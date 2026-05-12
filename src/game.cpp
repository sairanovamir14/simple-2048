#include "../include/game.h"

#include <cstdlib>

int board[SIZE][SIZE];

int score = 0;
int best = 0;

// Добавление числа
void addNumber()
{
    int x, y;

    do
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    while(board[y][x] != 0);

    board[y][x] = 2;
}

// Начало игры
void startGame()
{
    score = 0;

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            board[i][j] = 0;
        }
    }

    addNumber();
    addNumber();
}

bool canMove()
{
    // Есть пустая клетка
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(board[i][j] == 0)
            {
                return true;
            }
        }
    }

    // Проверка по горизонтали
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE - 1; j++)
        {
            if(board[i][j] == board[i][j + 1])
            {
                return true;
            }
        }
    }

    // Проверка по вертикали
    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 0; i < SIZE - 1; i++)
        {
            if(board[i][j] == board[i + 1][j])
            {
                return true;
            }
        }
    }

    return false;
}