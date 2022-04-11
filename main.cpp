#include <iostream>

#include "game.cpp"
#include "minimax.cpp"

#define AI_PLAYER WHITE
#define SEARCH_DEPTH 5

using namespace std;

int main() {
  Game *game = new Game();
  MiniMax minimax;

  Player winner;
  bool tie = false;
  do {
    cout << game->print_board();
    cout << "Current player: ";
    if (game->get_cur_player() == BLACK) {
      cout << "X";
    } else {
      cout << "O";
    }
    cout << "\n";

    while (true) {
      move_t move;
      if (game->get_cur_player() == AI_PLAYER) {
        int score = minimax.solve(game, SEARCH_DEPTH, &move);
        cout << "AI move (" << move.loc.row << ", " << move.loc.col
             << ") score: " << score << "\n";
      } else {
        int row, col;
        cout << "Enter your move, sir (row followed by col):\n";
        cin >> row;
        cin >> col;

        move = game->get_move(row, col);
      }
      Game *next_game = game->make_move(move);
      if (next_game != NULL) {
        delete game;
        game = next_game;
        break;
      }
    }

    cout << "\n\n";
  } while (!game->is_over(&winner, &tie));

  cout << game->print_board();
  cout << "Game over!\n";
  if (tie) {
    cout << "It was a tie\n";
  } else {
    cout << "The winner is: ";
    if (winner == BLACK) {
      cout << "X";
    } else {
      cout << "O";
    }
    cout << "\n";
  }
}
