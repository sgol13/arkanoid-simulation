# Arkanoid Simulation
This project is a simple multithreaded simulation inspired by the game [Arkanoid](https://en.wikipedia.org/wiki/Arkanoid). I've created it to improve my understanding of C++ multithreading and synchronization techniques. The simulation is randomized and runs according to the following rules:
* Players ( M ) want to destroy the wall ( X ) located above them. 
Each player is simulated in a separate thread what entails the need of synchronization. 
* Paddles ( \_ ) and balls ( o ) lie on the ground and can be picked up by players.
* When a player decides to damage the wall, he tries to collect a paddle and a ball. He uses the paddle to bounce the ball up and destroy some bricks. Then the player puts the paddle away. In the meantime, the ball falls onto the ground somewhere else.

As the described simulation rules may lead to deadlocks, I used some techniques concerning players' behaviour to prevent them.

<a href="https://youtu.be/CRSda9U3UgE">
         <img alt="Arkanoid Simulation video" src="https://i.postimg.cc/rmbCTrcS/play-screen.png" width=600">
</a>                                                                                                     

## Requirements
* CMake
* Make
* ncurses ([download](https://ftp.gnu.org/pub/gnu/ncurses/))

## Compilation
First, clone the repository.

```
git clone https://github.com/sgol13/arkanoid-simulation.git
cd arkanoid-simulation
```

Then you can use a prepared bash script to compile and run the program.
```
./run
```
The simulation can be stopped by pressing f.                                                                                               

## License
This project is under MIT [license](LICENSE).
