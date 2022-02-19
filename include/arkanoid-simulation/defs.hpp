// Szymon Golebiowski
// Arkanoid Simulation

#ifndef DEFS_HPP
#define DEFS_HPP

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <ncurses.h>
#include <thread>
#include <vector>

using namespace std;

// SET DIMENSIONS
constexpr int BOARD_HEIGHT = 25;
constexpr int BOARD_WIDTH = 70;
constexpr int WALL_HEIGHT = 5;

// SET OBJECTS
constexpr int N_BALLS = 3;
constexpr int N_PADDLES = 3;
constexpr int N_PLAYERS = 7;

// SET TIMES
constexpr int MULTIPLY_TIME = 12;

constexpr chrono::milliseconds PLAYER_MOVE_TIME(MULTIPLY_TIME * 5);
constexpr chrono::milliseconds BALL_MOVE_TIME(MULTIPLY_TIME * 3);

constexpr int MIN_HANG_AROUND = 20;
constexpr int MAX_HANG_AROUND = 80;

constexpr int CHANGE_DIR_MIN_TIME = 20;
constexpr int CHANGE_DIR_MAX_TIME = 50;
constexpr int PREPARATION_MIN_TIME = 100;
constexpr int PREPERATION_MAX_TIME = 180;

constexpr int PUT_AWAY_MIN_TIME = 2;
constexpr int PUT_AWAY_MAX_TIME = 10;

// GLOBAL
extern mutex lock_screen;
extern bool finish_flag;

// generates random time in range <a, b>
chrono::milliseconds randomTime(int a, int b);

// generates random value in range <a, b>
int random(int a, int b);

#endif