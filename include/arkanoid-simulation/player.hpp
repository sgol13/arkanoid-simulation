// Szymon Golebiowski
// Arkanoid Simulation

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "arkanoid-simulation/defs.hpp"
#include "arkanoid-simulation/game_objects.hpp"

class Player {
  public:
    int x;
    int direction; // 1 right -1 left
    int change_dir_time = 0;

    Wall &wall;
    array<Ball, N_BALLS> &balls;
    array<Paddle, N_PADDLES> &paddles;

    Ball *my_ball = nullptr;
    Paddle *my_paddle = nullptr;

    Player(Wall &_wall, array<Ball, N_BALLS> &_balls,
           array<Paddle, N_PADDLES> &_paddles);

    void draw();

    void remove();

    void move();

    void run();
};

#endif
