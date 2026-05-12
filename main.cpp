// Простая версия 2048
// SFML 3.0

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

const int SIZE = 4;

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

                score += board[i][j - 1];

                if(score > best)
                {
                    best = score;
                }

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

                score += board[i][j + 1];

                if(score > best)
                {
                    best = score;
                }

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

                score += board[i - 1][j];

                if(score > best)
                {
                    best = score;
                }

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

                score += board[i + 1][j];

                if(score > best)
                {
                    best = score;
                }

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
        sf::VideoMode({420, 560}),
        "2048"
    );

    sf::Font font;

    if(!font.openFromFile("arial.ttf"))
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