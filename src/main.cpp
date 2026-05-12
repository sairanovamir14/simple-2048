#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <string>

#include "../include/game.h"

using namespace std;

int main()
{
    srand(time(0));

    startGame();

    bool gameOver = false;

    sf::RenderWindow window(
        sf::VideoMode({420, 560}),
        "2048"
    );

    sf::Font font;

    if(!font.openFromFile("assets/arial.ttf"))
    {
        return 0;
    }

    // MAIN RESTART BUTTON
    sf::RectangleShape button(
        sf::Vector2f(140, 45)
    );

    button.setPosition(
        sf::Vector2f(140, 500)
    );

    button.setFillColor(
        sf::Color(130, 130, 130)
    );

    sf::Text buttonText(font);

    buttonText.setString("RESTART");

    buttonText.setCharacterSize(24);

    buttonText.setFillColor(
        sf::Color::White
    );

    buttonText.setPosition(
        sf::Vector2f(155, 505)
    );

    // SCORE
    sf::Text scoreText(font);

    scoreText.setCharacterSize(26);

    scoreText.setFillColor(
        sf::Color::White
    );

    // BEST
    sf::Text bestText(font);

    bestText.setCharacterSize(22);

    bestText.setFillColor(
        sf::Color::White
    );

    // GAME OVER PANEL
    sf::RectangleShape gameOverPanel(
        sf::Vector2f(260, 120)
    );

    gameOverPanel.setPosition(
        sf::Vector2f(80, 210)
    );

    gameOverPanel.setFillColor(
        sf::Color(245, 245, 245)
    );

    gameOverPanel.setOutlineThickness(5);

    gameOverPanel.setOutlineColor(
        sf::Color::Black
    );

    // GAME OVER TEXT
    sf::Text gameOverText(font);

    gameOverText.setString(
        "GAME OVER"
    );

    gameOverText.setCharacterSize(36);

    gameOverText.setFillColor(
        sf::Color(150, 20, 20)
    );

    // CENTER GAME OVER TEXT
    sf::FloatRect gameBounds =
        gameOverText.getLocalBounds();

    gameOverText.setPosition(
        sf::Vector2f(
            210 - gameBounds.size.x / 2,
            225
        )
    );

    // GAME OVER BUTTON
    sf::RectangleShape gameOverButton(
        sf::Vector2f(160, 45)
    );

    gameOverButton.setPosition(
        sf::Vector2f(130, 275)
    );

    gameOverButton.setFillColor(
        sf::Color(190, 180, 170)
    );

    // GAME OVER BUTTON TEXT
    sf::Text gameOverButtonText(font);

    gameOverButtonText.setString(
        "RESTART"
    );

    gameOverButtonText.setCharacterSize(28);

    gameOverButtonText.setFillColor(
        sf::Color::White
    );

    gameOverButtonText.setPosition(
        sf::Vector2f(155, 280)
    );

    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            // CLOSE
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // KEYBOARD
            if(const auto* key =
               event->getIf<sf::Event::KeyPressed>())
            {
                if(!gameOver)
                {
                    if(key->code ==
                       sf::Keyboard::Key::Left)
                    {
                        moveLeft();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Right)
                    {
                        moveRight();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Up)
                    {
                        moveUp();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Down)
                    {
                        moveDown();
                    }
                }

                // RESTART WITH R
                if(key->code ==
                   sf::Keyboard::Key::R)
                {
                    startGame();

                    gameOver = false;
                }

                // GAME OVER CHECK
                if(!canMove())
                {
                    gameOver = true;
                }
            }

            // MOUSE
            if(const auto* mouse =
               event->getIf
               <sf::Event::MouseButtonPressed>())
            {
                int mx = mouse->position.x;
                int my = mouse->position.y;

                // MAIN BUTTON
                if(mx >= 140 && mx <= 280
                   && my >= 500 && my <= 545)
                {
                    startGame();

                    gameOver = false;
                }

                // GAME OVER BUTTON
                if(gameOver)
                {
                    if(mx >= 130 && mx <= 290
                       && my >= 275 && my <= 320)
                    {
                        startGame();

                        gameOver = false;
                    }
                }
            }
        }

        // SCORE
        scoreText.setString(
            "SCORE: " + to_string(score)
        );

        bestText.setString(
            "BEST: " + to_string(best)
        );

        scoreText.setPosition(
            sf::Vector2f(140, 20)
        );

        bestText.setPosition(
            sf::Vector2f(165, 55)
        );

        // BACKGROUND
        window.clear(
            sf::Color(190, 180, 170)
        );

        // BOARD
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                sf::RectangleShape rect(
                    sf::Vector2f(80, 80)
                );

                rect.setPosition(
                    sf::Vector2f(
                        35 + j * 90,
                        120 + i * 90
                    )
                );

                rect.setFillColor(
                    sf::Color(205, 205, 205)
                );

                // TILE COLORS
                if(board[i][j] == 2)
                {
                    rect.setFillColor(
                        sf::Color(238, 228, 218)
                    );
                }

                if(board[i][j] == 4)
                {
                    rect.setFillColor(
                        sf::Color(237, 224, 200)
                    );
                }

                if(board[i][j] == 8)
                {
                    rect.setFillColor(
                        sf::Color(242, 177, 121)
                    );
                }

                if(board[i][j] == 16)
                {
                    rect.setFillColor(
                        sf::Color(245, 149, 99)
                    );
                }

                if(board[i][j] == 32)
                {
                    rect.setFillColor(
                        sf::Color(246, 124, 95)
                    );
                }

                if(board[i][j] == 64)
                {
                    rect.setFillColor(
                        sf::Color(246, 94, 59)
                    );
                }

                if(board[i][j] == 128)
                {
                    rect.setFillColor(
                        sf::Color(237, 207, 114)
                    );
                }

                if(board[i][j] == 256)
                {
                    rect.setFillColor(
                        sf::Color(237, 204, 97)
                    );
                }

                if(board[i][j] == 512)
                {
                    rect.setFillColor(
                        sf::Color(237, 200, 80)
                    );
                }

                if(board[i][j] == 1024)
                {
                    rect.setFillColor(
                        sf::Color(237, 197, 63)
                    );
                }

                if(board[i][j] == 2048)
                {
                    rect.setFillColor(
                        sf::Color(237, 194, 46)
                    );
                }

                window.draw(rect);

                // NUMBERS
                if(board[i][j] != 0)
                {
                    sf::Text text(font);

                    text.setString(
                        to_string(board[i][j])
                    );

                    text.setCharacterSize(30);

                    if(board[i][j] >= 8)
                    {
                        text.setFillColor(
                            sf::Color::White
                        );
                    }
                    else
                    {
                        text.setFillColor(
                            sf::Color::Black
                        );
                    }

                    // CENTER TEXT
                    sf::FloatRect bounds =
                        text.getLocalBounds();

                    text.setPosition(
                        sf::Vector2f(
                            35 + j * 90 +
                            40 - bounds.size.x / 2,

                            120 + i * 90 +
                            18
                        )
                    );

                    window.draw(text);
                }
            }
        }

        // DRAW UI
        window.draw(button);
        window.draw(buttonText);

        window.draw(scoreText);
        window.draw(bestText);

        // GAME OVER WINDOW
        if(gameOver)
        {
            window.draw(gameOverPanel);

            window.draw(gameOverText);

            window.draw(gameOverButton);

            window.draw(gameOverButtonText);
        }

        window.display();
    }

    return 0;
}