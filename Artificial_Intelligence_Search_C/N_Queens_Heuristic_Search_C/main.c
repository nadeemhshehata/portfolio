/* main.c
 *
 * Demo / GUI driver for n-queens MIN-CONFLICTS solver.
 */

#include "nqueens.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef USE_SDL_GUI
#include <SDL2/SDL.h>
#endif




/* Try to solve n-queens and report timing and correctness. */
static int run_solver(int n, long max_steps, int verbose) {
    NQueensBoard *board = nq_create(n);
    if (!board) {
        fprintf(stderr, "Failed to allocate board for n = %d\n", n);
        return 0;
    }

    unsigned int seed = (unsigned int)time(NULL);
    clock_t start = clock();
    int success = nq_min_conflicts(board, max_steps, seed);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    if (verbose) {
        printf("n = %d: %s (time = %.3f s)\n",
               n, success ? "solution found" : "no solution",
               elapsed);
    } else {
        printf("%d, %d, %.6f\n", n, success, elapsed);
    }

    if (success) {
            if (nq_is_solution(board)) {
                printf("Solution check: VALID N-Queens configuration.\n");
            } else {
                printf("Solution check: *** INVALID N-Queens configuration! ***\n");
            }
        } else {
            printf("Solution check: no solution found (nothing to verify).\n");
        }

    /* For small boards, print board */
    if (success && n <= 100) {
        nq_print_board(board, 100);
    }

#ifdef USE_SDL_GUI
    /* Optionally show GUI if board small enough */
    if (success && n <= 1000000) {
        printf("Launching SDL GUI (press esc to exit)...\n");
        /* run SDL GUI */
        /* We forward board to GUI function below */
        extern void show_board_sdl(const NQueensBoard *board);
        show_board_sdl(board);
    }
#endif

    nq_free(board);
    return success;
}

#ifdef USE_SDL_GUI

void show_board_sdl(const NQueensBoard *board) {
    int n = board->n;
    const int *queens = board->queens;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    const int window_size = 800;
    SDL_Window *win = SDL_CreateWindow(
        "N-Queens Solution",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_size, window_size,
        SDL_WINDOW_SHOWN
    );

    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }

    int base_cell_size = window_size / n;
    if (base_cell_size < 1) base_cell_size = 1;  /* minimum */

    float zoom    = 1.0f;   /* current zoom factor */
    float offsetX = 0.0f;   /* translation so we can zoom around mouse */
    float offsetY = 0.0f;

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                /* ESC closes window */
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                /* 0 key resets zoom and recenter */
                        else if (e.key.keysym.sym == SDLK_0) {
                            zoom = 1.0f;
                            offsetX = 0.0f;
                            offsetY = 0.0f;
                        }
            } else if (e.type == SDL_MOUSEWHEEL) {
                /* zoom in/out around current mouse position */
                int mx, my;
                SDL_GetMouseState(&mx, &my);

                float old_zoom = zoom;
                if (e.wheel.y < 0) {          /* scroll up = zoom in */
                    zoom *= 1.2f;
                } else if (e.wheel.y > 0) {   /* scroll down = zoom out */
                    zoom /= 1.2f;
                }

                if (zoom < 0.1f) zoom = 0.1f;
                if (zoom > 50.0f) zoom = 50.0f;

                float ratio = zoom / old_zoom;

                /* keep the board point under the mouse fixed on screen */
                offsetX = mx - (mx - offsetX) * ratio;
                offsetY = my - (my - offsetY) * ratio;
            }
        }

        int cell_size = (int)(base_cell_size * zoom);
        if (cell_size < 1) cell_size = 1;

        /* Clear background */
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        /* Draw chessboard squares: light/dark */
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                int dark = (row + col) % 2;

                if (dark) {
                    /* dark square (greenish) */
                    SDL_SetRenderDrawColor(ren, 118, 150, 86, 255);
                } else {
                    /* light square (beige) */
                    SDL_SetRenderDrawColor(ren, 238, 238, 210, 255);
                }

                SDL_Rect rect = {
                    (int)(offsetX + col * cell_size),
                    (int)(offsetY + row * cell_size),
                    cell_size,
                    cell_size
                };
                SDL_RenderFillRect(ren, &rect);
            }
        }

        /* Draw queens as gold circles in the center of each square */
        SDL_SetRenderDrawColor(ren, 220, 190, 30, 255);  /* queen color */

        for (int col = 0; col < n; ++col) {
            int row = queens[col];

            int cx = (int)(offsetX + col * cell_size + cell_size / 2);
            int cy = (int)(offsetY + row * cell_size + cell_size / 2);
            int r  = cell_size * 3 / 8;
            if (r < 1) r = 1;

            for (int dy = -r; dy <= r; ++dy) {
                for (int dx = -r; dx <= r; ++dx) {
                    if (dx*dx + dy*dy <= r*r) {
                        SDL_RenderDrawPoint(ren, cx + dx, cy + dy);
                    }
                }
            }
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#endif /* USE_SDL_GUI */



/* Main:
 * Usage:
 *   ./nqueens n
 *
 * Examples:
 *   ./nqueens 10
 *   ./nqueens 100
 *   ./nqueens 1000
 *
 * For timing experiments over several n, you could modify this to loop.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        fprintf(stderr, "Example: %s 1000\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return 1;
    }

    /* A reasonable default for max_steps:
     * e.g., 100 * n (you can tune this).
     */
    long max_steps = 100L * (long)n;

    /* Always use verbose = 1 so we get lines like:
       "n = 10: solution found (time = 0.000 s)" */
    int verbose = 1;
    run_solver(n, max_steps, verbose);

    return 0;
}
