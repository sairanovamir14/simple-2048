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
        sf::VideoMode({850, 550}),
        "2048 Visual C++"
    );

    sf::Font font;

    if(!font.openFromFile("assets/arial.ttf"))
    {
        return 0;
    }

    // TITLE
    sf::Text title(font);

    title.setString("2048");

    title.setCharacterSize(80);

    title.setFillColor(
        sf::Color(120, 110, 100)
    );

    title.setPosition(
        sf::Vector2f(560, 120)
    );

    // SCORE BOX
    sf::RectangleShape scoreBox(
        sf::Vector2f(280, 90)
    );

    scoreBox.setPosition(
        sf::Vector2f(500, 250)
    );

    scoreBox.setFillColor(
        sf::Color(190, 180, 170)
    );

    // SCORE LABEL
    sf::Text scoreLabel(font);

    scoreLabel.setString("SCORE");

    scoreLabel.setCharacterSize(24);

    scoreLabel.setFillColor(
        sf::Color::White
    );

    scoreLabel.setPosition(
        sf::Vector2f(610, 260)
    );

    // SCORE NUMBER
    sf::Text scoreNumber(font);

    scoreNumber.setCharacterSize(40);

    scoreNumber.setFillColor(
        sf::Color::White
    );

    // CONTROLS
    sf::Text controls(font);

    controls.setString(
        "Use arrows or WASD"
    );

    controls.setCharacterSize(28);

    controls.setFillColor(
        sf::Color(120, 110, 100)
    );

    controls.setPosition(
        sf::Vector2f(520, 390)
    );

    // RESTART INFO
    sf::Text restartInfo(font);

    restartInfo.setString(
        "R restart   Esc quit"
    );

    restartInfo.setCharacterSize(22);

    restartInfo.setFillColor(
        sf::Color(160, 150, 140)
    );

    restartInfo.setPosition(
        sf::Vector2f(560, 450)
    );

    // GAME OVER PANEL
    sf::RectangleShape gameOverPanel(
        sf::Vector2f(300, 150)
    );

    gameOverPanel.setPosition(
        sf::Vector2f(270, 180)
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

    gameOverText.setCharacterSize(40);

    gameOverText.setFillColor(
        sf::Color(150, 20, 20)
    );

    sf::FloatRect gameBounds =
        gameOverText.getLocalBounds();

    gameOverText.setPosition(
        sf::Vector2f(
            425 - gameBounds.size.x / 2,
            205
        )
    );

    // GAME OVER BUTTON
    sf::RectangleShape gameOverButton(
        sf::Vector2f(170, 50)
    );

    gameOverButton.setPosition(
        sf::Vector2f(340, 260)
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
        sf::Vector2f(360, 268)
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
                if(key->code ==
                   sf::Keyboard::Key::Escape)
                {
                    window.close();
                }

                if(!gameOver)
                {
                    if(key->code ==
                       sf::Keyboard::Key::Left
                       || key->code ==
                       sf::Keyboard::Key::A)
                    {
                        moveLeft();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Right
                       || key->code ==
                       sf::Keyboard::Key::D)
                    {
                        moveRight();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Up
                       || key->code ==
                       sf::Keyboard::Key::W)
                    {
                        moveUp();
                    }

                    if(key->code ==
                       sf::Keyboard::Key::Down
                       || key->code ==
                       sf::Keyboard::Key::S)
                    {
                        moveDown();
                    }
                }

                // RESTART
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

                // GAME OVER BUTTON
                if(gameOver)
                {
                    if(mx >= 340 && mx <= 510
                       && my >= 260 && my <= 310)
                    {
                        startGame();

                        gameOver = false;
                    }
                }
            }
        }

        // SCORE UPDATE
        scoreNumber.setString(
            to_string(score)
        );

        sf::FloatRect scoreBounds =
            scoreNumber.getLocalBounds();

        scoreNumber.setPosition(
            sf::Vector2f(
                640 - scoreBounds.size.x / 2,
                290
            )
        );

        // BACKGROUND
        window.clear(
            sf::Color(250, 248, 239)
        );

        // BOARD
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                sf::RectangleShape rect(
                    sf::Vector2f(90, 90)
                );

                rect.setPosition(
                    sf::Vector2f(
                        40 + j * 100,
                        70 + i * 100
                    )
                );

                rect.setFillColor(
                    sf::Color(205, 193, 180)
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

                    text.setCharacterSize(36);

                    if(board[i][j] >= 8)
                    {
                        text.setFillColor(
                            sf::Color::White
                        );
                    }
                    else
                    {
                        text.setFillColor(
                            sf::Color(120,110,100)
                        );
                    }

                    sf::FloatRect bounds =
                        text.getLocalBounds();

                    text.setPosition(
                        sf::Vector2f(
                            40 + j * 100 +
                            45 - bounds.size.x / 2,

                            70 + i * 100 +
                            18
                        )
                    );

                    window.draw(text);
                }
            }
        }

        // DRAW UI
        window.draw(title);

        window.draw(scoreBox);

        window.draw(scoreLabel);

        window.draw(scoreNumber);

        window.draw(controls);

        window.draw(restartInfo);

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