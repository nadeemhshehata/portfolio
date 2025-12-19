/* nqueens.c
 *
 * Implementation of n-queens MIN-CONFLICTS algorithm.
 */

#include "nqueens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Internal helpers for diagonal indices */
static inline int diag1_index(int n, int row, int col) {
    /* main diagonal: row - col in [-(n-1), +(n-1)]
       shift by (n-1) to make index non-negative */
    return row - col + (n - 1);
}

static inline int diag2_index(int n, int row, int col) {
    /* anti-diagonal: row + col in [0, 2n-2] */
    return row + col;
}

NQueensBoard *nq_create(int n) {
    if (n <= 0) return NULL;

    NQueensBoard *board = (NQueensBoard *)malloc(sizeof(NQueensBoard));
    if (!board) return NULL;

    board->n = n;
    board->queens = (int *)malloc(sizeof(int) * n);
    if (!board->queens) {
        free(board);
        return NULL;
    }

    /* Initialize queens to row 0 (will be randomized later) */
    for (int i = 0; i < n; ++i) {
        board->queens[i] = 0;
    }

    return board;
}

void nq_free(NQueensBoard *board) {
    if (!board) return;
    free(board->queens);
    free(board);
}

int nq_is_solution(const NQueensBoard *board) {
    if (!board || !board->queens) return 0;
    int n = board->n;
    const int *queens = board->queens;

    if (n <= 0) return 0;

    /* Row and diagonal occupancy */
    int *rows   = (int *)calloc(n, sizeof(int));
    int *diag1  = (int *)calloc(2 * n - 1, sizeof(int));
    int *diag2  = (int *)calloc(2 * n - 1, sizeof(int));

    if (!rows || !diag1 || !diag2) {
        free(rows);
        free(diag1);
        free(diag2);
        return 0;
    }

    for (int col = 0; col < n; ++col) {
        int row = queens[col];
        if (row < 0 || row >= n) {
            free(rows);
            free(diag1);
            free(diag2);
            return 0;
        }

        int d1 = diag1_index(n, row, col);
        int d2 = diag2_index(n, row, col);

        rows[row]++;
        diag1[d1]++;
        diag2[d2]++;

        if (rows[row] > 1 || diag1[d1] > 1 || diag2[d2] > 1) {
            free(rows);
            free(diag1);
            free(diag2);
            return 0; /* conflict found */
        }
    }

    free(rows);
    free(diag1);
    free(diag2);
    return 1; /* no conflicts */
}

int nq_min_conflicts(NQueensBoard *board, long max_steps, unsigned int seed) {
    if (!board || !board->queens) return 0;
    int n = board->n;
    int *queens = board->queens;

    if (n <= 0) return 0;
    if (n == 2 || n == 3) return 0; /* no solution for these cases */

    srand(seed);

    /* Conflict arrays */
    int *row_conflicts   = (int *)calloc(n, sizeof(int));
    int *diag1_conflicts = (int *)calloc(2 * n - 1, sizeof(int));
    int *diag2_conflicts = (int *)calloc(2 * n - 1, sizeof(int));

    if (!row_conflicts || !diag1_conflicts || !diag2_conflicts) {
        free(row_conflicts);
        free(diag1_conflicts);
        free(diag2_conflicts);
        return 0;
    }

    /* Random initial placement: one queen per column */
    for (int col = 0; col < n; ++col) {
        int row = rand() % n;
        queens[col] = row;

        int d1 = diag1_index(n, row, col);
        int d2 = diag2_index(n, row, col);

        row_conflicts[row]++;
        diag1_conflicts[d1]++;
        diag2_conflicts[d2]++;
    }

    /* Helper buffer for conflicted columns and candidate rows */
    int *conflicted_cols = (int *)malloc(sizeof(int) * n);
    int *candidate_rows  = (int *)malloc(sizeof(int) * n);

    if (!conflicted_cols || !candidate_rows) {
        free(row_conflicts);
        free(diag1_conflicts);
        free(diag2_conflicts);
        free(conflicted_cols);
        free(candidate_rows);
        return 0;
    }

    long step;
    for (step = 0; step < max_steps; ++step) {
        /* Build list of conflicted columns */
        int conflicted_count = 0;
        for (int col = 0; col < n; ++col) {
            int row = queens[col];
            int d1 = diag1_index(n, row, col);
            int d2 = diag2_index(n, row, col);

            /* number of QUEENS on this row/diags minus itself */
            int conflicts_here =
                (row_conflicts[row] - 1) +
                (diag1_conflicts[d1] - 1) +
                (diag2_conflicts[d2] - 1);

            if (conflicts_here > 0) {
                conflicted_cols[conflicted_count++] = col;
            }
        }

        if (conflicted_count == 0) {
            /* Found solution */
            free(row_conflicts);
            free(diag1_conflicts);
            free(diag2_conflicts);
            free(conflicted_cols);
            free(candidate_rows);
            return 1;
        }

        /* Pick a random conflicted column */
        int random_index = rand() % conflicted_count;
        int col = conflicted_cols[random_index];
        int current_row = queens[col];

        /* Find row with minimum conflicts in this column */
        int min_conflicts = n * 3; /* upper bound */
        int candidate_count = 0;

        for (int r = 0; r < n; ++r) {
            int d1 = diag1_index(n, r, col);
            int d2 = diag2_index(n, r, col);

            int conflicts =
                row_conflicts[r] +
                diag1_conflicts[d1] +
                diag2_conflicts[d2];

            /* If r == current_row, moving queen to its current spot
               would count itself 3 times; subtract that to measure
               actual conflicts with OTHER queens. */
            if (r == current_row) {
                conflicts -= 3;
            }

            if (conflicts < min_conflicts) {
                min_conflicts = conflicts;
                candidate_rows[0] = r;
                candidate_count = 1;
            } else if (conflicts == min_conflicts) {
                candidate_rows[candidate_count++] = r;
            }
        }

        /* Pick a random row among the best candidates */
        int new_row = candidate_rows[rand() % candidate_count];

        if (new_row != current_row) {
            /* Update conflict structures */
            int old_d1 = diag1_index(n, current_row, col);
            int old_d2 = diag2_index(n, current_row, col);
            int new_d1 = diag1_index(n, new_row, col);
            int new_d2 = diag2_index(n, new_row, col);

            row_conflicts[current_row]--;
            diag1_conflicts[old_d1]--;
            diag2_conflicts[old_d2]--;

            queens[col] = new_row;

            row_conflicts[new_row]++;
            diag1_conflicts[new_d1]++;
            diag2_conflicts[new_d2]++;
        }
        /* else do nothing; already at a minimal-conflict row */
    }

    /* No solution found within max_steps */
    free(row_conflicts);
    free(diag1_conflicts);
    free(diag2_conflicts);
    free(conflicted_cols);
    free(candidate_rows);

    return nq_is_solution(board); /* usually 0 */
}

void nq_print_board(const NQueensBoard *board, int max_print_size) {
    if (!board || !board->queens) return;
    int n = board->n;
    const int *queens = board->queens;

    int limit = n;
    if (limit > max_print_size && max_print_size > 0) {
        limit = max_print_size;
    }

    printf("Board (n = %d):\n", n);

    if (n <= max_print_size) {
        /* Print full board with 'Q' and '.' */
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                if (queens[col] == row) {
                    printf("Q ");
                } else {
                    printf(". ");
                }
            }
            printf("\n");
        }
    } else {
        /* For large boards, just print coordinates and first few rows/cols */
        printf("First %d columns (col: row):\n", limit);
        for (int col = 0; col < limit; ++col) {
            printf("(%d: %d) ", col, queens[col]);
            if ((col + 1) % 10 == 0) printf("\n");
        }
        printf("\n... (remaining columns omitted)\n");
    }
}
