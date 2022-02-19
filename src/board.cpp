// Szymon Golebiowski
// Arkanoid Simulation

#include "arkanoid-simulation/board.hpp"

Board::Board() {

    // print the frame
    mvprintw(0, 0, string(BOARD_WIDTH, '_').c_str());
    mvprintw(BOARD_HEIGHT, 0, string(BOARD_WIDTH, '_').c_str());
    for (int y = 1; y <= BOARD_HEIGHT; y++) {
        mvprintw(y, 0, "|");
        mvprintw(y, BOARD_WIDTH, "|");
    }

    // set the objects
    while (players.size() < N_PLAYERS) {
        players.push_back(Player(wall, balls, paddles));
        players.back().x = random(3, BOARD_WIDTH - 3);
        players.back().draw();
    }

    for (auto &ball : balls) {
        ball.y = BOARD_HEIGHT + 1;
        ball.x = random(1, BOARD_WIDTH - 1);
        ball.draw();
    }

    for (auto &paddle : paddles) {
        paddle.x = random(1, BOARD_WIDTH - 1);
        paddle.draw();
    }

    refresh();
}

// starts the simulation
void Board::simulation() {

    vector<thread> threads;

    for (auto &player : players)
        threads.push_back(thread(&Player::run, &player));

    int character = 0;
    while (character != 'f')
        character = getch();

    finish_flag = true;

    for (auto &thread : threads)
        thread.join();
}
