#include <string.h>

#include <chrono>
#include <iostream>

#include "alphabeta.h"
#include "game.h"
#include "minimax.h"
#include "paraalphabeta.h"
#include "paraminimax.h"
#include "player.h"

using namespace std;

using namespace chrono;
typedef chrono::high_resolution_clock Clock;
typedef chrono::duration<double> dsec;

int main(int argc, char **argv) {
  if (argc < 4) {
    cout << "Too few arguments\n";
    return 1;
  }

  int num_procs = atoi(argv[1]);
  omp_set_num_threads(num_procs);

  char *solver_str = argv[2];

  Game *game = new Game();
  MiniMax minimax;
  AlphaBeta alphabeta;

  ParaMiniMax paraminimax;
  ParaAlphaBeta paraalphabeta;

  Solver *solver;
  if (strcmp(solver_str, "minimax") == 0) {
    solver = &minimax;
  } else if (strcmp(solver_str, "alphabeta") == 0) {
    solver = &alphabeta;
  } else if (strcmp(solver_str, "paraminimax") == 0) {
    solver = &paraminimax;
  } else if (strcmp(solver_str, "paraalphabeta") == 0) {
    solver = &paraalphabeta;
  } else {
    cout << "Invalid choice\n";
    return 1;
  }

  int search_depth = atoi(argv[3]);

  auto compute_start = Clock::now();
  double compute_time = 0;
  int num_moves = 0;

  Player winner;
  bool tie = false;
  do {
    cout << game->print_board();
    cout << "Current player: ";
    if (game->get_cur_player() == Player::BLACK) {
      cout << "X";
    } else {
      cout << "O";
    }
    cout << "\n";

    while (true) {
      auto move_start = Clock::now();
      double move_time = 0;
      move_t move;
      int score = solver->solve(game, search_depth, &move);
      cout << "AI move (" << move.loc.row << ", " << move.loc.col
           << ") score: " << score << "\n";

      Game *next_game = game->make_move(move);
      move_time += duration_cast<dsec>(Clock::now() - move_start).count();
      num_moves++;
      printf("Move Time: %lf\n", move_time);
      if (next_game != NULL) {
        delete game;
        game = next_game;
        break;
      }
    }

    cout << "\n\n";
  } while (!game->is_over(&winner, &tie));

  compute_time += duration_cast<dsec>(Clock::now() - compute_start).count();

  cout << game->print_board();
  cout << "Game over!\n";
  if (tie) {
    cout << "It was a tie\n";
  } else {
    cout << "The winner is: ";
    if (winner == Player::BLACK) {
      cout << "X";
    } else {
      cout << "O";
    }
    cout << "\n";
  }

  printf("\nTotal Compute Time: %lf\nAverage Move Time: %lf (%d moves)\n",
         compute_time, compute_time / num_moves, num_moves);
}
