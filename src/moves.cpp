#include "../include/game.h"

// Влево
void moveLeft()
{
    bool moved = false;

    for(int k = 0; k < 4; k++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 1; j < SIZE; j++)
            {
                if(board[i][j - 1] == 0
                   && board[i][j] != 0)
                {
                    board[i][j - 1] = board[i][j];
                    board[i][j] = 0;

                    moved = true;
                }
            }
        }
    }

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 1; j < SIZE; j++)
        {
            if(board[i][j - 1] == board[i][j]
               && board[i][j] != 0)
            {
                board[i][j - 1] *= 2;

                moved = true;

                score += board[i][j - 1];

                if(score > best)
                {
                    best = score;
                }

                board[i][j] = 0;
            }
        }
    }

    if(moved)
    {
        addNumber();
    }
}

// Вправо
void moveRight()
{
    bool moved = false;

    for(int k = 0; k < 4; k++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 2; j >= 0; j--)
            {
                if(board[i][j + 1] == 0
                   && board[i][j] != 0)
                {
                    board[i][j + 1] = board[i][j];
                    board[i][j] = 0;

                    moved = true;
                }
            }
        }
    }

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 2; j >= 0; j--)
        {
            if(board[i][j + 1] == board[i][j]
               && board[i][j] != 0)
            {
                board[i][j + 1] *= 2;

                moved = true;

                score += board[i][j + 1];

                if(score > best)
                {
                    best = score;
                }

                board[i][j] = 0;
            }
        }
    }

    if(moved)
    {
        addNumber();
    }
}

// Вверх
void moveUp()
{
    bool moved = false;

    for(int k = 0; k < 4; k++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int i = 1; i < SIZE; i++)
            {
                if(board[i - 1][j] == 0
                   && board[i][j] != 0)
                {
                    board[i - 1][j] = board[i][j];
                    board[i][j] = 0;

                    moved = true;
                }
            }
        }
    }

    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 1; i < SIZE; i++)
        {
            if(board[i - 1][j] == board[i][j]
               && board[i][j] != 0)
            {
                board[i - 1][j] *= 2;

                moved = true;

                score += board[i - 1][j];

                if(score > best)
                {
                    best = score;
                }

                board[i][j] = 0;
            }
        }
    }

    if(moved)
    {
        addNumber();
    }
}

// Вниз
void moveDown()
{
    bool moved = false;

    for(int k = 0; k < 4; k++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int i = 2; i >= 0; i--)
            {
                if(board[i + 1][j] == 0
                   && board[i][j] != 0)
                {
                    board[i + 1][j] = board[i][j];
                    board[i][j] = 0;

                    moved = true;
                }
            }
        }
    }

    for(int j = 0; j < SIZE; j++)
    {
        for(int i = 2; i >= 0; i--)
        {
            if(board[i + 1][j] == board[i][j]
               && board[i][j] != 0)
            {
                board[i + 1][j] *= 2;

                moved = true;

                score += board[i + 1][j];

                if(score > best)
                {
                    best = score;
                }

                board[i][j] = 0;
            }
        }
    }

    if(moved)
    {
        addNumber();
    }
}