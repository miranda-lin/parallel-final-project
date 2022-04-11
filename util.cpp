#include "player.cpp"

struct coord_t {
  int row;
  int col;
};

struct move_t {
  Player player;
  coord_t loc;
};
