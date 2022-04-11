class Solver {
 public:
  virtual int solve(Game *node, int depth, move_t *best_move) = 0;

  Solver() {}

 protected:
  int evaluate_state(Game *node) {
    int score = 0;
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (node->get_square(i, j) == MAXIE) {
          score++;
        } else if (node->get_square(i, j) == MINIE) {
          score--;
        }
      }
    }
    return score;
  }
};
