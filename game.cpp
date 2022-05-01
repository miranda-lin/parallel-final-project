#include "game.h"

#include <assert.h>

coord_t UP = (coord_t){-1, 0};
coord_t DOWN = (coord_t){1, 0};
coord_t LEFT = (coord_t){0, -1};
coord_t RIGHT = (coord_t){0, 1};
coord_t LEFT_UP = (coord_t){-1, -1};
coord_t RIGHT_UP = (coord_t){-1, 1};
coord_t LEFT_DOWN = (coord_t){-1, 1};
coord_t RIGHT_DOWN = (coord_t){1, 1};
coord_t FLANK_DIRECTIONS[] = {UP,      DOWN,     LEFT,      RIGHT,
                              LEFT_UP, RIGHT_UP, LEFT_DOWN, RIGHT_DOWN};

vector<move_t> Game::list_legal_moves() {
  vector<move_t> moves;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      move_t move =
          (move_t){.player = cur_player, (coord_t){.row = i, .col = j}};
      if (is_move_legal(move)) {
        moves.push_back(move);
      }
    }
  }
  return moves;
}

Game *Game::make_move(move_t move) {
  if (!is_move_legal(move)) {
    return NULL;
  }

  // copy the current game state
  Game *next_state = new Game();
  next_state->cur_player = cur_player;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      next_state->board[i][j] = board[i][j];
    }
  }

  // get the board pieces to flip
  vector<coord_t> all_to_flip;
  for (int i = 0; i < 8; i++) {
    coord_t direction = FLANK_DIRECTIONS[i];
    coord_t cur_pos = move.loc;
    vector<coord_t> to_flip;  // temp vector

    do {
      cur_pos.row += direction.row;
      cur_pos.col += direction.col;
      Player piece = next_state->board[cur_pos.row][cur_pos.col];

      if (piece == move.player) {
        all_to_flip.insert(all_to_flip.end(), to_flip.begin(), to_flip.end());
        break;
      } else if (piece == Player::NONE) {
        break;
      }

      to_flip.push_back(cur_pos);
    } while (is_coord_legal(cur_pos));
  }

  // flip the pieces
  for (coord_t pos : all_to_flip) {
    next_state->board[pos.row][pos.col] = move.player;
  }

  // place the new piece
  next_state->board[move.loc.row][move.loc.col] = move.player;

  // swap players
  if (next_state->cur_player == Player::BLACK) {
    next_state->cur_player = Player::WHITE;
  } else {
    assert(next_state->cur_player == Player::WHITE);
    next_state->cur_player = Player::BLACK;
  }

  // return new game state
  return next_state;
}

move_t Game::get_move(int row, int col) {
  return (move_t){.player = cur_player,
                  .loc = (coord_t){.row = row, .col = col}};
}

bool Game::is_over(Player *winner, bool *tie) {
  if (!list_legal_moves().empty()) {
    return false;
  }

  int black_pts = 0;
  int white_pts = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == Player::BLACK) {
        black_pts++;
      } else if (board[i][j] == Player::WHITE) {
        white_pts++;
      }
    }
  }

  if (black_pts < white_pts) {
    *winner = Player::WHITE;
  } else if (black_pts > white_pts) {
    *winner = Player::BLACK;
  } else {
    *tie = true;
  }

  return true;
}

Player Game::get_cur_player() { return cur_player; }

Player Game::get_square(int row, int col) { return board[row][col]; }

string Game::print_board() {
  string output = "  ";
  for (int j = 0; j < COLS; j++) {
    output.append(to_string(j));
    output.append(" ");
  }
  output.append("\n");
  for (int i = 0; i < ROWS; i++) {
    output.append(to_string(i));
    output.append(" ");

    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == Player::BLACK) {
        output.append("X");
      } else if (board[i][j] == Player::WHITE) {
        output.append("O");
      } else {
        output.append(" ");
      }
      output.append(" ");
    }
    output.append("\n");
  }
  return output;
}

Game::Game() {
  cur_player = Player::BLACK;

  // set board to all empty
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = Player::NONE;
    }
  }

  // place initial pieces
  board[ROWS / 2 - 1][COLS / 2 - 1] = Player::WHITE;
  board[ROWS / 2 - 1][COLS / 2] = Player::BLACK;
  board[ROWS / 2][COLS / 2 - 1] = Player::BLACK;
  board[ROWS / 2][COLS / 2] = Player::WHITE;
}

bool Game::is_coord_legal(coord_t coord) {
  return 0 <= coord.row && coord.row < ROWS && 0 <= coord.col &&
         coord.col < COLS;
}

bool Game::is_move_legal(move_t move) {
  if (move.player != cur_player) {
    return false;
  }

  if (board[move.loc.row][move.loc.col] != Player::NONE) {
    return false;
  }

  for (int i = 0; i < 8; i++) {
    coord_t direction = FLANK_DIRECTIONS[i];
    coord_t cur_pos = move.loc;
    int num_chomped = 0;
    do {
      cur_pos.row += direction.row;
      cur_pos.col += direction.col;
      Player piece = board[cur_pos.row][cur_pos.col];

      if (piece == move.player) {
        return num_chomped > 0;
      } else if (piece == Player::NONE) {
        break;
      }

      num_chomped++;
    } while (is_coord_legal(cur_pos));
  }

  return false;
}
