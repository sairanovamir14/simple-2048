#pragma once

const int SIZE = 4;

extern int board[SIZE][SIZE];

extern int score;
extern int best;

// game.cpp
void addNumber();
void startGame();

// moves.cpp
void moveLeft();
void moveRight();
void moveUp();
void moveDown();