// Szymon Golebiowski
// Arkanoid Simulation

#include "arkanoid-simulation/board.hpp"
#include "arkanoid-simulation/defs.hpp"

mutex lock_screen;
bool finish_flag;

// generates random time in range <a, b>
chrono::milliseconds randomTime(int a, int b) {
    return chrono::milliseconds(rand() % (b - a + 1) + a);
}

// generates random value in range <a, b>
int random(int a, int b) { return (rand() % (b - a + 1)) + a; }

int main() {
    srand(time(NULL));

    initscr();
    noecho();
    curs_set(0);

    Board arkanoid;
    arkanoid.simulation();

    refresh();

    endwin();
    return 0;
}
