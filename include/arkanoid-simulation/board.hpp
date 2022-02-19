// Szymon Golebiowski
// Arkanoid Simulation

#ifndef BOARD_HPP
#define BOARD_HPP

#include "arkanoid-simulation/defs.hpp"
#include "arkanoid-simulation/game_objects.hpp"
#include "arkanoid-simulation/player.hpp"

class Board {
  private:
    Wall wall;
    array<Ball, N_BALLS> balls;
    array<Paddle, N_PADDLES> paddles;
    vector<Player> players;

  public:
    // constructor
    Board();

    // starts the simulation
    void simulation();
};



#endif