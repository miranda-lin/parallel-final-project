#ifndef GAME_H
#define GAME_H

#define ROWS 8
#define COLS 8

#include <string>
#include <vector>

#include "move.h"
#include "player.h"

using namespace std;

class Game {
 public:
  vector<move_t> list_legal_moves();

  Game *make_move(move_t move);

  move_t get_move(int row, int col);

  bool is_over(Player *winner, bool *tie);

  Player get_cur_player();

  Player get_square(int row, int col);

  string print_board();

  Game();

 private:
  Player board[ROWS][COLS];
  Player cur_player;

  bool is_coord_legal(coord_t coord);

  bool is_move_legal(move_t move);
};

#endif
