// Szymon Golebiowski
// Arkanoid Simulation

#include "arkanoid-simulation/player.hpp"

// constructor
Player::Player(Wall &_wall, array<Ball, N_BALLS> &_balls,
               array<Paddle, N_PADDLES> &_paddles)
    : wall(_wall), balls(_balls), paddles(_paddles) {}

// draws the player at the current position
void Player::draw() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(BOARD_HEIGHT, x, "M");
    if (my_ball)
        mvprintw(BOARD_HEIGHT - 1, x, "o");
    if (my_paddle)
        mvprintw(BOARD_HEIGHT - 1, x, "_");
    refresh();
}

// removes the ball
void Player::remove() {
    lock_guard<mutex> temp_lock(lock_screen);
    mvprintw(BOARD_HEIGHT, x, "_");
    if (my_ball)
        mvprintw(BOARD_HEIGHT - 1, x, " ");
    if (my_paddle)
        mvprintw(BOARD_HEIGHT - 1, x, " ");
    refresh();
}

// moves one tile
void Player::move() {
    this_thread::sleep_for(PLAYER_MOVE_TIME);
    remove();
    if (x + direction == 0 || x + direction == BOARD_WIDTH) {
        direction *= -1;
        change_dir_time = random(CHANGE_DIR_MIN_TIME, CHANGE_DIR_MAX_TIME);
    } else if (change_dir_time-- == 0) {
        direction *= -1;
        change_dir_time = random(CHANGE_DIR_MIN_TIME, CHANGE_DIR_MAX_TIME);
    }

    x += direction;
    draw();
}

// simulates the activity of a player
void Player::run() {
    direction = (rand() % 2) ? 1 : -1;

    while (!finish_flag) {
        // hanging around
        int moves = random(MIN_HANG_AROUND, MAX_HANG_AROUND);
        while (moves--) {
            move();
            if (finish_flag)
                return;
        }

        // preparing
        moves = random(PREPARATION_MIN_TIME, PREPERATION_MAX_TIME);
        while ((!my_paddle || !my_ball) && moves--) {
            move();
            if (finish_flag) {
                if (my_ball)
                    my_ball->m.unlock();
                if (my_paddle)
                    my_paddle->m.unlock();

                return;
            }

            // check ball
            if (!my_ball)
                for (int i = 0; i < balls.size(); i++)
                    if (balls[i].x == x && balls[i].m.try_lock()) {
                        my_ball = &balls[i];
                        my_ball->remove();
                        break;
                    }

            // check paddle
            if (!my_paddle)
                for (int i = 0; i < paddles.size(); i++)
                    if (paddles[i].x == x && paddles[i].m.try_lock()) {
                        my_paddle = &paddles[i];
                        my_paddle->remove();
                        break;
                    }
        }

        if (my_ball && my_paddle) {

            lock_screen.lock();
            mvprintw(BOARD_HEIGHT - 1, x, "_");
            refresh();
            lock_screen.unlock();

            my_ball->x = x;
            my_ball->y = BOARD_HEIGHT - 2;

            int ball_dir_x = (rand() % 2) ? 1 : -1;
            int ball_dir_y = -1;

            while (my_ball->y != BOARD_HEIGHT + 1) {
                if (finish_flag) {
                    my_ball->m.unlock();
                    my_paddle->m.unlock();
                    return;
                }

                if (my_ball->y != BOARD_HEIGHT) {
                    my_ball->draw();
                    draw();
                    this_thread::sleep_for(BALL_MOVE_TIME);
                    my_ball->remove();
                } else
                    this_thread::sleep_for(BALL_MOVE_TIME);

                // brick
                if (my_ball->y < BOARD_HEIGHT - 1) {
                    if (wall.hit(my_ball->y + ball_dir_y, my_ball->x))
                        ball_dir_y *= -1;

                    if (wall.hit(my_ball->y, my_ball->x + ball_dir_x))
                        ball_dir_x *= -1;
                }

                // right
                if (my_ball->x + ball_dir_x == BOARD_WIDTH)
                    ball_dir_x *= -1;
                // left
                if (my_ball->x + ball_dir_x == 0)
                    ball_dir_x *= -1;
                // up
                if (my_ball->y + ball_dir_y == 0)
                    ball_dir_y *= -1;

                my_ball->x += ball_dir_x;
                my_ball->y += ball_dir_y;
            }

            my_ball->draw();
            my_ball->m.unlock();
            my_ball = nullptr;

            // put the paddle away
            int moves = random(PUT_AWAY_MIN_TIME, PUT_AWAY_MAX_TIME);
            while (moves--) {
                move();
                if (finish_flag) {
                    my_paddle->m.unlock();
                    return;
                }
            }

            my_paddle->x = x;
            my_paddle->draw();
            my_paddle->m.unlock();
            my_paddle = nullptr;

            lock_screen.lock();
            mvprintw(BOARD_HEIGHT - 1, x, " ");
            lock_screen.unlock();

        } else if (my_ball) {
            my_ball->x = x;
            my_ball->draw();
            my_ball->m.unlock();

            lock_guard<mutex> temp_lock(lock_screen);
            mvprintw(BOARD_HEIGHT - 1, x, " ");
            my_ball = nullptr;

        } else if (my_paddle) {
            my_paddle->x = x;
            my_paddle->draw();
            my_paddle->m.unlock();

            lock_guard<mutex> temp_lock(lock_screen);
            mvprintw(BOARD_HEIGHT - 1, x, " ");
            my_paddle = nullptr;
        }
    }
}