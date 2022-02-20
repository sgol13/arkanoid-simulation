// Szymon Golebiowski
// Arkanoid Simulation

#include "arkanoid-simulation/game_objects.hpp"

//=================================================================================
// WALL

Wall::Wall() {

    bricks.resize(BOARD_HEIGHT);
    for (auto &row : bricks)
        row.resize(BOARD_WIDTH, false);

    for (int y = 1; y <= WALL_HEIGHT; y++)
        for (int x = 1; x < BOARD_WIDTH; x++) {
            bricks[y][x] = true;
            mvprintw(y, x, "X");
        }
}

// removes the brick from a given position (from the memory and from the screen)
bool Wall::hit(int y, int x) {

    lock_guard<mutex> temp_wall_lock(m);
    if (bricks[y][x]) {
        bricks[y][x] = false;
        lock_guard<mutex> temp_lock(lock_screen);
        mvprintw(y, x, " ");
        refresh();
        return true;
    }
    return false;
}

//=================================================================================
// BALL

// draws the ball at the current position
void Ball::draw() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(y, x, "o");
    refresh();
}

// removes the ball
void Ball::remove() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(y, x, " ");
    refresh();
}

//=================================================================================
// PADDLE

// draws the ball at the current position
void Paddle::draw() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(BOARD_HEIGHT + 1, x, "_");
    refresh();
}

// removes the ball
void Paddle::remove() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(BOARD_HEIGHT + 1, x, " ");
    refresh();
}
