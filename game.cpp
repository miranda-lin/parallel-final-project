#define ROWS 8
#define COLS 8

#include <string>
#include <vector>

#include "player.cpp"

using namespace std;

struct move_t {
  Player player;
  coord_t loc;
};

struct coord_t {
  int row;
  int col;
};

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

class Game {
 public:
  bool make_move(move_t move) {
    if (!is_move_legal(move)) {
      return false;
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
        Player piece = board[cur_pos.row][cur_pos.col];

        if (piece == move.player) {
          all_to_flip.insert(all_to_flip.end(), to_flip.begin(), to_flip.end());
          break;
        } else if (piece == NONE) {
          break;
        }

        to_flip.push_back(cur_pos);
      } while (is_coord_legal(cur_pos));
    }

    // flip the pieces
    for (coord_t pos : all_to_flip) {
      board[pos.row][pos.col] = move.player;
    }

    // place the new piece
    board[move.loc.row][move.loc.col] = move.player;

    // swap players
    if (cur_player == BLACK) {
      cur_player = WHITE;
    } else {
      assert(cur_player == WHITE);
      cur_player = BLACK;
    }
    return true;
  }

  vector<move_t> list_legal_moves() {
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

  bool is_over(Player *winner, bool *tie) {
    if (!list_legal_moves().empty()) {
      return false;
    }

    int black_pts = 0;
    int white_pts = 0;
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (board[i][j] == BLACK) {
          black_pts++;
        } else if (board[i][j] == WHITE) {
          white_pts++;
        }
      }
    }

    if (black_pts < white_pts) {
      *winner = WHITE;
    } else if (black_pts > white_pts) {
      *winner = BLACK;
    } else {
      *tie = true;
    }

    return true;
  }

  Player get_cur_player() { return cur_player; }

  string print_board() {
    string output = "";
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (board[i][j] == BLACK) {
          output.append("X");
        } else if (board[i][j] == WHITE) {
          output.append("O");
        } else {
          output.append(" ");
        }
      }
      output.append("\n");
    }
    return output;
  }

  Game() {
    cur_player = BLACK;

    // place initial pieces
    board[ROWS / 2][COLS / 2] = WHITE;
    board[ROWS / 2][COLS / 2 + 1] = BLACK;
    board[ROWS / 2 + 1][COLS / 2] = BLACK;
    board[ROWS / 2 + 1][COLS / 2 + 1] = WHITE;
  }

 private:
  Player board[ROWS][COLS];
  Player cur_player;

  bool is_coord_legal(coord_t coord) {
    return 0 <= coord.row && coord.row < ROWS && 0 <= coord.col &&
           coord.col < COLS;
  }

  bool is_move_legal(move_t move) {
    if (move.player != cur_player) {
      return false;
    }

    if (board[move.loc.row][move.loc.col] != NONE) {
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
        } else if (piece == NONE) {
          break;
        }

        num_chomped++;
      } while (is_coord_legal(cur_pos));
    }

    return false;
  }
};
