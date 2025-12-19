#include "sudoku_csp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




LogLevel g_log = LOG_SUMMARY; // default: concise, demo-friendly

#define LOG_SUM(...)    do { if (g_log >= LOG_SUMMARY) printf(__VA_ARGS__); } while(0)
#define LOG_TRACE_(...) do { if (g_log >= LOG_TRACE)   printf(__VA_ARGS__); } while(0)

Stats g_stats = {0};

// ---- Helpers ----
static void aq_init(ArcQueue* q) {
    q->head = q->tail = q->size = 0;
    memset(q->inq, 0, sizeof(q->inq));
}

static void aq_push(ArcQueue* q, int i, int j) {
    if (i==j) return;
    if (q->inq[i][j]) return; // dedupe
    if (q->size >= (int)(sizeof(q->items)/sizeof(q->items[0]))) {
        // Guard: should not happen with dedupe
        fprintf(stderr, "!! Queue capacity reached (unexpected). Dropping arc (%d,%d).\n", i, j);
        return;
    }
    q->items[q->tail] = (Arc){i,j};
    q->tail = (q->tail + 1) % (int)(sizeof(q->items)/sizeof(q->items[0]));
    q->size++;
    q->inq[i][j] = true;
}

static Arc aq_pop(ArcQueue* q) {
    Arc a = q->items[q->head];
    q->head = (q->head + 1) % (int)(sizeof(q->items)/sizeof(q->items[0]));
    q->size--;
    q->inq[a.i][a.j] = false;
    return a;
}

static Dom full_domain(void){ return 0x3FE; } // bits 1..9 -> 0b11_1111_1110

static void add_peer(CSP* c, int a, int b) {
    if (a==b) return;
    for (int k=0;k<c->peer_count[a];++k) if (c->peers[a][k]==b) return;
    c->peers[a][c->peer_count[a]++] = b;
}

void csp_init(CSP* csp) {
    for (int i=0;i<NCELLS;++i) {
        csp->dom[i] = full_domain();
        csp->peer_count[i]=0;
    }
    // build peers: row, col, box (all-different via pairwise inequality)
    for (int r=0;r<N;++r){
        for (int c=0;c<N;++c){
            int i = cell(r,c);
            for (int cc=0; cc<N; ++cc) add_peer(csp, i, cell(r,cc));
            for (int rr=0; rr<N; ++rr) add_peer(csp, i, cell(rr,c));
            int r0 = (r/3)*3, c0 = (c/3)*3;
            for (int dr=0; dr<3; ++dr) for (int dc=0; dc<3; ++dc) add_peer(csp, i, cell(r0+dr, c0+dc));
        }
    }
}

void csp_from_grid(CSP* c, const char* g81) {
    // g81 = 81 chars row-major, '.' or '0' means blank
    for (int i=0;i<NCELLS;++i) c->dom[i] = full_domain();
    for (int i=0;i<NCELLS;++i){
        char ch = g81[i];
        if (ch>='1' && ch<='9'){
            int v = ch - '0';
            c->dom[i] = singleton_mask(v);
        }
    }
}

static void print_line(void){
    printf("+=======+=======+=======+\n");
}

static void print_cell_val(Dom d){
    if (popcount(d)==1) printf("%d", first_value(d));
    else printf(".");
}

void csp_print_board(const CSP* c, const char* title){
    if (title) printf("%s\n", title);
    print_line();
    for (int r=0;r<N;++r){
        printf("| ");
        for (int c0=0;c0<3;++c0){
            for (int c1=0;c1<3;++c1){
                int cidx = c0*3 + c1;
                int i = cell(r, cidx);
                print_cell_val(c->dom[i]);
                if (c1<2) printf(" ");
            }
            printf("| ");
        }
        printf("\n");
        if ((r%3)==2) print_line();
    }
}

// remove value v from domain[i]; return true if removed
static bool remove_val(CSP* c, int i, int v){
    Dom before = c->dom[i];
    c->dom[i] &= (Dom)~singleton_mask(v);
    return c->dom[i] != before;
}

// REVISE(xi, xj): remove a in Di if no b in Dj with b != a (inequality constraint)
static int revise(CSP* c, int xi, int xj){
    Dom Di = c->dom[xi];
    Dom Dj = c->dom[xj];
    int removed = 0;
        for (int v=1; v<=9; ++v){
            if (!(Di & (1u<<v))) continue;
            bool supported = false;
            for (int b=1; b<=9; ++b){
                if (!(Dj & (1u<<b))) continue;
                if (b != v){ supported = true; break; }
            }
            if (!supported){
                if (remove_val(c, xi, v)) ++removed;
            }
        }
        return removed;
    }


static void enqueue_all_arcs(const CSP* c, ArcQueue* q){
    for (int i=0;i<NCELLS;++i){
        for (int k=0;k<c->peer_count[i];++k){
            int j = c->peers[i][k];
            if (i!=j) aq_push(q, i, j);
        }
    }
}

// AC-3 with concise, assignment-style logging
bool ac3(CSP* c, bool verbose){
	clock_t t0 = clock();
    ArcQueue q; aq_init(&q);
    enqueue_all_arcs(c, &q);

    int step = 0, reductions = 0, singletons = 0;
    const int show_example_count = 3;   // print first 3 singletons
    const int progress_every_sing = 5;  // then every 5 singletons
    bool printed_midway_snapshot = false;

    if (verbose && g_log >= LOG_SUMMARY) {
        LOG_SUM("== Running AC-3 (arc-consistency) ==\n");
        LOG_SUM("AC-3 = constraint propagation: prune values that can’t work with neighbors.\n");
        LOG_SUM("AC-3: enforcing arc-consistency (initial arcs: %d)\n", q.size);
    }

    const int progress_every_step = 250; // TRACE heartbeat

    while (q.size > 0){
        Arc a = aq_pop(&q);
        ++g_stats.ac3_pops;
        int xi = a.i, xj = a.j;

        if (verbose && g_log >= LOG_TRACE) {
            LOG_TRACE_("  pop "); print_rc(xi); printf(" -> "); print_rc(xj);
            printf("   (queue=%d)\n", q.size);
        }

        int removed = revise(c, xi, xj);
        if (removed > 0){
            ++reductions;
            g_stats.ac3_value_removals += removed;

            if (c->dom[xi] == 0){
                if (verbose && g_log >= LOG_SUMMARY) {
                    printf("AC-3: contradiction (domain wipeout at ");
                    print_rc(xi); printf(")\n");
                }
                g_stats.ac3_ms += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
                return false;
            }

            if (popcount(c->dom[xi]) == 1){
                ++singletons;
                if (verbose && g_log >= LOG_SUMMARY) {
                    int v = first_value(c->dom[xi]);
                    if (singletons <= show_example_count){
                        printf("AC-3: assign "); print_rc(xi); printf(" \xe2\x86\x90 %d (singleton)\n", v);
                    } else if (singletons % progress_every_sing == 0){
                        printf("AC-3: progress: %d singletons so far…\n", singletons);
                    }
                    if (!printed_midway_snapshot && singletons == show_example_count){
                        csp_print_board(c, NULL);
                        printed_midway_snapshot = true;
                    }
                }
            }

            // *** ONLY WHEN DOMAIN CHANGED ***
            for (int t=0; t<c->peer_count[xi]; ++t){
                int xk = c->peers[xi][t];
                if (xk == xj) continue;
                aq_push(&q, xk, xi);
            }
        }

        if (verbose && g_log >= LOG_TRACE && (++step % progress_every_step) == 0){
            LOG_TRACE_("  ...progress: processed=%d, queue=%d, reductions=%d, singles=%d\n",
                       step, q.size, reductions, singletons);
        }
    }


    if (verbose && g_log >= LOG_SUMMARY) {
        LOG_SUM("AC-3: finished (reductions=%d, singletons=%d)\n", reductions, singletons);
        // Board once at end of AC-3
        csp_print_board(c, NULL);
    }
    g_stats.ac3_ms += (double)(clock() - t0) * 1000.0 / CLOCKS_PER_SEC;
    return true;
}

bool is_solved(const CSP* c){
    for (int i=0;i<NCELLS;++i) if (popcount(c->dom[i])!=1) return false;
    return true;
}

static int select_mrv(const CSP* c){
    int best=-1, best_count=10;
    for (int i=0;i<NCELLS;++i){
        int pc = popcount(c->dom[i]);
        if (pc>1 && pc<best_count){ best=i; best_count=pc; if (pc==2) break; }
    }
    return best;
}

static CSP clone_csp(const CSP* c){
    CSP t = *c; // shallow copy ok
    return t;
}

static bool assign(CSP* c, int i, int v){
    // set dom[i] = {v}
    Dom others = c->dom[i] & (Dom)~singleton_mask(v);
    c->dom[i] = singleton_mask(v);
    (void)others; // minimal forward checks omitted here
    return true;
}

// ---- I/O helpers ----
static void load_grid_from_file(const char* path, char* out81){
    FILE* f = fopen(path, "r");
    if (!f){ perror("open puzzle"); exit(1); }

    int n = 0;
    char line[256];

    while (fgets(line, sizeof(line), f) && n < 81) {
        // Skip lines that are comments, e.g. // ... or leading spaces then //
        char* p = line;
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '/' && p[1] == '/') {
            continue;  // whole line is a comment
        }

        // Otherwise, pull out just '.', '0', and digits 1..9
        for (; *p && n < 81; ++p) {
            char ch = *p;
            if (ch == '.' || ch == '0' || (ch >= '1' && ch <= '9')) {
                out81[n++] = ch;
            }
        }
    }
    fclose(f);
        if (n != 81){
            fprintf(stderr, "Puzzle file must contain exactly 81 valid chars; got %d.\n", n);
            exit(1);
        }
    }

static void default_grid(char* g81){
    // Same deterministic puzzle as your sample
    const char* rows[9] = {
    	    "8........",
    	    "..36.....",
    	    ".7..9.2..",
    	    ".5...7...",
    	    "....457..",
    	    "...1..3.",
    	    "..1....68",
			"..85...1.",
			".9....4..",

    };
    int p=0;
    for (int r=0;r<9;++r) for (int c=0;c<9;++c){
        char ch = rows[r][c];
        g81[p++] = (ch==0)?'.':ch;
    }
}

bool backtrack(CSP* c, bool verbose){
    // Goal test
    if (is_solved(c)) return true;

    // VARIABLE SELECTION: MRV (Minimum Remaining Values)
    int i = select_mrv(c);
    Dom D = c->dom[i];
    if (D == 0) return false;

    // Try values in ascending order
    for (int v = 1; v <= 9; ++v){
        if (!(D & (1u << v))) continue;
        ++g_stats.search_nodes;
        if (verbose && g_log >= LOG_SUMMARY){
            printf("Decide "); print_rc(i); printf(" = %d (MRV)\n", v);
        }

        CSP t = clone_csp(c);

        if (!assign(&t, i, v)){
            if (verbose && g_log >= LOG_TRACE){
                printf("  reject (peer conflict) "); print_rc(i); printf(" = %d\n", v);
            }
            continue;
        }

        // Quiet propagation during search to keep demo clean
        if (!ac3(&t, /*verbose=*/false)){
        	++g_stats.backtracks;

            if (verbose && g_log >= LOG_SUMMARY){
                printf("  contradiction after propagation — backtrack from ");
                print_rc(i); printf(" = %d\n", v);
            }
            continue;
        }

        if (backtrack(&t, verbose)){
            *c = t; // keep solution
            return true;
        }
        ++g_stats.backtracks;
        if (verbose && g_log >= LOG_TRACE){
            printf("  backtrack (dead end) "); print_rc(i); printf(" = %d\n", v);
        }
    }
    return false;
}

int main(int argc, char** argv){
    clock_t start = clock();
    CSP csp; csp_init(&csp);

    // parse flags and also remember the first non-flag argument as the path
    const char* path = NULL;
    for (int a = 1; a < argc; ++a) {
        if (strcmp(argv[a], "--quiet") == 0)      { g_log = LOG_QUIET; }
        else if (strcmp(argv[a], "--summary") == 0){ g_log = LOG_SUMMARY; }
        else if (strcmp(argv[a], "--trace") == 0)  { g_log = LOG_TRACE; }
        else if (argv[a][0] != '-' && !path)       { path = argv[a]; } // <-- capture path
    }

    char g81[82] = {0};
    if (path) {
        if (strcmp(path, ".") == 0) {
            memset(g81, '.', 81);                  // empty board when "." is passed
        } else {
            load_grid_from_file(path, g81);        // <-- your loader
        }
    } else {
        if (g_log >= LOG_SUMMARY)
            printf("Generated puzzle (deterministic) .\n");
        default_grid(g81);
    }

    csp_from_grid(&csp, g81);
    csp_print_board(&csp, NULL); // board at start (given)

    bool solved = false;
    const char* solved_by = "Unsolved";

    // --- AC-3 phase ---
    if (!ac3(&csp, true)){
        if (g_log >= LOG_SUMMARY) printf("Inconsistent during AC-3.\n");
        solved = false;
        solved_by = "Contradiction";
    } else if (is_solved(&csp)){
        if (g_log >= LOG_SUMMARY) printf("== Solved by constraint propagation (AC-3) ==\n");
        csp_print_board(&csp, NULL);
        solved = true;
        solved_by = "AC-3";
    } else {
        // --- Search phase (only if needed) ---
        if (g_log >= LOG_SUMMARY){
            printf("== Entering search (backtracking with MRV) ==\n");
            printf("Backtracking = try a choice, propagate, undo if it fails.\n");
        }
        if (backtrack(&csp, true)){
            if (g_log >= LOG_SUMMARY) printf("== Solved ==\n");
            csp_print_board(&csp, NULL);
            solved = true;
            solved_by = "Search";
        } else {
            if (g_log >= LOG_SUMMARY) printf("No solution found.\n");
            solved = false;
            solved_by = "Unsolved";
        }
    }

    // --- Final timing & report ---
    g_stats.total_ms = (double)(clock() - start) * 1000.0 / CLOCKS_PER_SEC;
    g_stats.solved_by = solved_by;

    // Print the requested summary
    printf("\n=== Summary ===\n");
    printf("AC-3 Pops: %ld\n", g_stats.ac3_pops);
    printf("Domains Reduced: %ld\n", g_stats.ac3_value_removals);
    printf("AC-3 Time (ms): %.3f\n", g_stats.ac3_ms);
    printf("Search Nodes: %ld\n", g_stats.search_nodes);
    printf("Backtracks: %ld\n", g_stats.backtracks);
    printf("Total Time (ms): %.3f\n", g_stats.total_ms);
    printf("Solved By: %s\n", g_stats.solved_by);

    return 0;
}
