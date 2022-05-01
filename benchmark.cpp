#include <chrono>
#include <iostream>

#include "alphabeta.h"
#include "game.h"
#include "minimax.h"
#include "paraminimax.h"
#include "player.h"

using namespace std;

int main() {
  Game *game = new Game();
  MiniMax minimax;
  AlphaBeta alphabeta;

  ParaMiniMax paraminimax;

  cout << "1 - minimax, 2 - alphabeta, 3 - paraminimax, 4 - paraalphabeta\n";
  cout << "Choose a solver: ";
  int solver_n;
  cin >> solver_n;

  Solver *solver;
  switch (solver_n) {
    case 1:
      solver = &minimax;
      break;
    case 2:
      solver = &alphabeta;
      break;
    case 3:
      solver = &paraminimax;
      break;
    case 4:
      cout << "Solver not implemented\n";
      return 1;
    default:
      cout << "Invalid choice\n";
      return 1;
  }

  cout << "Enter search depth: ";
  int search_depth;
  cin >> search_depth;

  cout << "Print game states (1/0)? ";
  int print_n;
  cin >> print_n;

  bool print_output;
  switch (print_n) {
    case 0:
      print_output = false;
      break;
    case 1:
      print_output = true;
      break;
    default:
      cout << "Invalid choice\n";
      return 1;
  }

  using namespace chrono;
  typedef chrono::high_resolution_clock Clock;
  typedef chrono::duration<double> dsec;

  auto compute_start = Clock::now();
  double compute_time = 0;

  Player winner;
  bool tie = false;
  do {
    if (print_output) {
      cout << game->print_board();
      cout << "Current player: ";
      if (game->get_cur_player() == Player::BLACK) {
        cout << "X";
      } else {
        cout << "O";
      }
      cout << "\n";
    }

    while (true) {
      auto move_start = Clock::now();
      double move_time = 0;
      move_t move;
      int score = solver->solve(game, search_depth, &move);
      cout << "AI move (" << move.loc.row << ", " << move.loc.col
           << ") score: " << score << "\n";

      Game *next_game = game->make_move(move);
      move_time += duration_cast<dsec>(Clock::now() - move_start).count();
      printf("Move Time: %lf.\n", move_time);
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
  printf("Compute Time: %lf.\n", compute_time);
}
