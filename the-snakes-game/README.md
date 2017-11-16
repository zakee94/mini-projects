# The Snakes Game
This is the classic game of snakes, in which the player controls a snake and eats "food" to grow. The game ends when the snake touches itself.

## Features
* Ability to increase/decrease speed of the snake right in the middle of the game !
* No limit on the length of the snake
* Dynamic scoring system based on the speed of the snake, more the speed more the score.
* Dynamic growing system based on the speed of the snake, more the speed more the grow.

## Built with
This game is coded in C using OpenGL libraries for the games graphics.

## How to run the game
Since the game uses OpenGL, make sure you have OpneGl/GLUT libraries set up in your environment. An example is given below in Linux(Ubuntu) on how to install these libraries:

Open up a terminal and execute the following commands:
```
sudo apt-get install freeglut3-dev
```
This will install GLUT on the system. Once this is done change to the directory in which snakes.c is present and execute the following commands in the terminal:
```
gcc snakes.c -lGL -lGLU -lglut
./a.out
```

## Game Controls
* Use WADS keys to control the snake
* Use P to increase the speed of the snake
* Use L to decrease the speed of the snake

## To change size of the window
Edit the line in main():
```
glutInitWindowSize(1024, 768);
```
and change the length and breadth to your preffered size. Default is 1024*768.

## Screenshot
![](https://drive.google.com/uc?id=1aOFcpQueuKuubKPQeoSWNhesEJO0EJFs)
