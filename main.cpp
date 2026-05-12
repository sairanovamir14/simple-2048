// Простая версия 2048
// SFML 3.0

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

const int SIZE = 4;

int board[SIZE][SIZE];

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

// Влево
void moveLeft()
{
    for(int k = 0; k < 4; k++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 1; j < SIZE; j++)
            {
                if(board[i][j - 1] == 0)
                {
                    board[i][j - 1] = board[i][j];
                    board[i][j] = 0;
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
                board[i][j] = 0;
            }
        }
    }

    addNumber();
}

// Вправо
void moveRight()
{
    for(int k = 0; k < 4; k++)
    {
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 2; j >= 0; j--)
            {
                if(board[i][j + 1] == 0)
                {
                    board[i][j + 1] = board[i][j];
                    board[i][j] = 0;
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
                board[i][j] = 0;
            }
        }
    }

    addNumber();
}

// Вверх
void moveUp()
{
    for(int k = 0; k < 4; k++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int i = 1; i < SIZE; i++)
            {
                if(board[i - 1][j] == 0)
                {
                    board[i - 1][j] = board[i][j];
                    board[i][j] = 0;
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
                board[i][j] = 0;
            }
        }
    }

    addNumber();
}

// Вниз
void moveDown()
{
    for(int k = 0; k < 4; k++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int i = 2; i >= 0; i--)
            {
                if(board[i + 1][j] == 0)
                {
                    board[i + 1][j] = board[i][j];
                    board[i][j] = 0;
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
                board[i][j] = 0;
            }
        }
    }

    addNumber();
}

int main()
{
    srand(time(0));

    startGame();

    sf::RenderWindow window(
        sf::VideoMode({420, 470}),
        "2048"
    );

    sf::Font font;

    if(!font.openFromFile("arial.ttf"))
    {
        return 0;
    }

    // Кнопка restart
    sf::RectangleShape button(
        sf::Vector2f(140, 40)
    );

    button.setPosition(
        sf::Vector2f(140, 415)
    );

    button.setFillColor(
        sf::Color(100, 100, 100)
    );

    sf::Text buttonText(font);

    buttonText.setString("RESTART");

    buttonText.setCharacterSize(24);

    buttonText.setFillColor(
        sf::Color::White
    );

    buttonText.setPosition(
        sf::Vector2f(155, 418)
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

            // Кнопка restart мышкой
            if(const auto* mouse =
               event->getIf
               <sf::Event::MouseButtonPressed>())
            {
                int mx = mouse->position.x;
                int my = mouse->position.y;

                if(mx >= 140 && mx <= 280
                   && my >= 415 && my <= 455)
                {
                    startGame();
                }
            }
        }

        window.clear(
            sf::Color(180, 170, 160)
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
                        10 + i * 100
                    )
                );

                rect.setFillColor(
                    sf::Color(220, 220, 220)
                );

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
                            35 + i * 100
                        )
                    );

                    window.draw(text);
                }
            }
        }

        // Кнопка
        window.draw(button);
        window.draw(buttonText);

        window.display();
    }

    return 0;
}