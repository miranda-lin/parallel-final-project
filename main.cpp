#include <iostream>

#include "game.cpp"

using namespace std;

int main() {
  Game game = Game();

  Player winner;
  bool tie = false;
  do {
    cout << game.print_board();
    cout << "Current player: ";
    if (game.get_cur_player() == BLACK) {
      cout << "X";
    } else {
      cout << "O";
    }
    cout << "\n";

    int row, col;
    do {
      cout << "Enter your move, sir (row followed by col):\n";
      cin >> row;
      cin >> col;
    } while (!game.submit_move(row, col));

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
  } while (!game.is_over(&winner, &tie));
}
