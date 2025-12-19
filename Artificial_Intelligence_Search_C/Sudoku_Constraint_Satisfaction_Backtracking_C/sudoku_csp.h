#ifndef SUDOKU_CSP_H
#define SUDOKU_CSP_H
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>

#define N 9
#define NCELLS 81
#define MAX_PEERS 20

// Bitmask domain: bit k (1<<k) represents value k (1..9). Bit 0 unused.
typedef uint16_t Dom;

typedef struct {
    Dom dom[NCELLS];          // current domains
    int peers[NCELLS][MAX_PEERS];
    int peer_count[NCELLS];
} CSP;

// Directed arc (xi -> xj) by cell indices 0..80
typedef struct { int i, j; } Arc;

typedef struct {
    Arc items[NCELLS * MAX_PEERS]; // upper bound = 81*20 = 1620
    int head, tail, size;
    bool inq[NCELLS][NCELLS];      // inq[i][j] true iff arc (i,j) currently enqueued
} ArcQueue;

// API
void csp_init(CSP* csp);
void csp_from_grid(CSP* csp, const char* grid81); // 81 chars
void csp_print_board(const CSP* csp, const char* title);
bool ac3(CSP* csp, bool verbose);
bool is_solved(const CSP* csp);
bool backtrack(CSP* csp, bool verbose);

// Utilities
static inline int cell(int r, int c) { return r * N + c; }
static inline int row_of(int idx) { return idx / N; }
static inline int col_of(int idx) { return idx % N; }
static inline int box_of(int r, int c) { return (r/3)*3 + (c/3); }
static inline Dom singleton_mask(int v) { return (Dom)(1u << v); }
static inline int popcount(Dom m) { return __builtin_popcount((unsigned)m); }
static inline int first_value(Dom m) { for (int v=1; v<=9; ++v) if (m & (1u<<v)) return v; return 0; }

// ---- Logging levels ----
typedef enum { LOG_QUIET = 0, LOG_SUMMARY = 1, LOG_TRACE = 2 } LogLevel;
extern LogLevel g_log;

// Pretty RrCc helpers
static inline void print_rc(int idx) {
    printf("R%dC%d", row_of(idx)+1, col_of(idx)+1);
}

// ---- Solver statistics ----
typedef struct {
    long ac3_pops;             // number of arc pops processed by AC-3
    long ac3_value_removals;   // total value deletions from domains during AC-3
    double ac3_ms;             // AC-3 wall time (ms)
    long search_nodes;         // number of value-attempt nodes in backtracking
    long backtracks;           // number of failed attempts (contradictions or dead ends)
    double total_ms;           // overall wall time (ms)
    const char* solved_by;     // "AC-3", "Search", "Unsolved", or "Contradiction"
} Stats;

extern Stats g_stats;


#endif
