/* nqueens.h
 *
 * N-Queens solver using MIN-CONFLICTS local search.
 * Representation: queens[col] = row, for col in [0, n-1].
 */

#ifndef NQUEENS_H
#define NQUEENS_H

#include <stddef.h>

/* Board structure */
typedef struct {
    int n;          /* board size (n x n) */
    int *queens;    /* queens[col] = row */
} NQueensBoard;

/* Create an empty board of size n (queens initialized to 0).
 * Returns NULL on allocation failure.
 */
NQueensBoard *nq_create(int n);

/* Free a board created by nq_create. */
void nq_free(NQueensBoard *board);

/* Check if the current configuration is a valid n-queens solution.
 * Returns 1 if solution, 0 otherwise.
 */
int nq_is_solution(const NQueensBoard *board);

/* Run MIN-CONFLICTS on the given board.
 *
 * - max_steps: maximum number of iterations (e.g., 10*n or 100*n).
 * - seed: random seed (e.g., time(NULL)).
 *
 * The function:
 *   1. Randomly initializes a configuration.
 *   2. Runs MIN-CONFLICTS until either:
 *        - a solution is found (returns 1), or
 *        - max_steps is reached (returns 0).
 *
 * For n == 2 or n == 3, returns 0 immediately (no solution).
 */
int nq_min_conflicts(NQueensBoard *board, long max_steps, unsigned int seed);

/* Pretty-print the board to stdout.
 *
 * - max_print_size: if board->n > max_print_size, prints only the first
 *   max_print_size rows/columns and summarizes the rest.
 */
void nq_print_board(const NQueensBoard *board, int max_print_size);

#endif /* NQUEENS_H */
