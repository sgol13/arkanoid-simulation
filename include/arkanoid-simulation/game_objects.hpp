// Szymon Golebiowski
// Arkanoid Simulation

#include "arkanoid-simulation/defs.hpp"

#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

//=================================================================================
// WALL

class Wall {
  private:
    vector<vector<bool>> bricks;
    mutex m;

  public:
    // constructor
    Wall();

    // removes the brick from a given position (from the memory and from the screen)
    bool hit(int y, int x);
};

//=================================================================================
// BALL

class Ball {
  public:
    int y, x;
    mutex m;

    // draws the ball at the current position
    void draw();

    // removes the ball
    void remove();
};

//=================================================================================
// PADDLE

class Paddle {
  public:
    int x;
    mutex m;

    // draws the paddle at the current position
    void draw();

    // removes the paddle
    void remove();
};

#endif