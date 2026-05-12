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

    sf::RenderWindow window(
        sf::VideoMode({420, 560}),
        "2048"
    );

    sf::Font font;

    if(!font.openFromFile("assets/arial.ttf"))
    {
        return 0;
    }

    // Кнопка restart
    sf::RectangleShape button(
        sf::Vector2f(140, 45)
    );

    button.setPosition(
        sf::Vector2f(20, 20)
    );

    button.setFillColor(
        sf::Color(120, 120, 120)
    );

    sf::Text buttonText(font);

    buttonText.setString("RESTART");

    buttonText.setCharacterSize(24);

    buttonText.setFillColor(
        sf::Color::White
    );

    buttonText.setPosition(
        sf::Vector2f(35, 25)
    );

    // SCORE
    sf::Text scoreText(font);

    scoreText.setCharacterSize(28);

    scoreText.setFillColor(
        sf::Color::White
    );

    // BEST
    sf::Text bestText(font);

    bestText.setCharacterSize(24);

    bestText.setFillColor(
        sf::Color::White
    );

    while(window.isOpen())
    {
        while(auto event = window.pollEvent())
        {
            // Закрытие окна
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Клавиши
            if(const auto* key =
               event->getIf<sf::Event::KeyPressed>())
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

                // Restart по R
                if(key->code ==
                   sf::Keyboard::Key::R)
                {
                    startGame();
                }
            }

            // Restart мышкой
            if(const auto* mouse =
               event->getIf
               <sf::Event::MouseButtonPressed>())
            {
                int mx = mouse->position.x;
                int my = mouse->position.y;

                if(mx >= 20 && mx <= 160
                   && my >= 20 && my <= 65)
                {
                    startGame();
                }
            }
        }

        scoreText.setString(
            "SCORE: " + to_string(score)
        );

        bestText.setString(
            "BEST: " + to_string(best)
        );

        scoreText.setPosition(
            sf::Vector2f(190, 15)
        );

        bestText.setPosition(
            sf::Vector2f(190, 55)
        );

        window.clear(
            sf::Color(190, 180, 170)
        );

        // Поле
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                sf::RectangleShape rect(
                    sf::Vector2f(90, 90)
                );

                rect.setPosition(
                    sf::Vector2f(
                        10 + j * 100,
                        120 + i * 100
                    )
                );

                rect.setFillColor(
                    sf::Color(220, 220, 220)
                );

                // Цвета плиток
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

                // Числа
                if(board[i][j] != 0)
                {
                    sf::Text text(font);

                    text.setString(
                        to_string(board[i][j])
                    );

                    text.setCharacterSize(30);

                    text.setFillColor(
                        sf::Color::Black
                    );

                    text.setPosition(
                        sf::Vector2f(
                            40 + j * 100,
                            145 + i * 100
                        )
                    );

                    window.draw(text);
                }
            }
        }

        // Интерфейс
        window.draw(button);
        window.draw(buttonText);

        window.draw(scoreText);
        window.draw(bestText);

        window.display();
    }

    return 0;
}