#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "ObstacleManager.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window({800, 600}, "Bike Game");

    // 1) Load font
    sf::Font font;
    if (!font.loadFromFile("assets/font/arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }

    // 2) Create menu texts
    sf::Text menuItems[2];
    menuItems[0].setFont(font);
    menuItems[0].setString("Start Game");
    menuItems[0].setCharacterSize(36);
    menuItems[0].setPosition(300, 200);

    menuItems[1].setFont(font);
    menuItems[1].setString("Exit");
    menuItems[1].setCharacterSize(36);
    menuItems[1].setPosition(300, 300);

    // Track which menu item is selected: 0 = Start, 1 = Exit
    int selected = 0;

    // 3) Menu loop
    while (window.isOpen()) {
        // highlight selection
        for (int i = 0; i < 2; ++i) {
            if (i == selected)
                menuItems[i].setFillColor(sf::Color::Yellow);
            else
                menuItems[i].setFillColor(sf::Color::White);
        }

        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed) {
                window.close();
            }
            else if (evt.type == sf::Event::KeyPressed) {
                if (evt.key.code == sf::Keyboard::Up || evt.key.code == sf::Keyboard::W) {
                    selected = (selected + 1) % 2;       // move up/down
                }
                else if (evt.key.code == sf::Keyboard::Down || evt.key.code == sf::Keyboard::S) {
                    selected = (selected + 1) % 2;
                }
                else if (evt.key.code == sf::Keyboard::Enter) {
                    if (selected == 0) {
                        // Start Game
                        goto GAME_LOOP;
                    } else {
                        // Exit
                        window.close();
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(menuItems[0]);
        window.draw(menuItems[1]);
        window.display();
    }

    return 0;

GAME_LOOP:
    // 4) Initialize your game objects
    Player player("assets/img/bik.png");
    ObstacleManager obstacleManager(2.0f, 0.1f);

    // Main game loop
    while (window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::Closed)
                window.close();
        }

        // Input, update, collision
        player.handleInput();
        player.update(window);
        obstacleManager.update(window);

        if (obstacleManager.checkCollision(player.getGlobalBounds())) {
            std::cout << "💥 Hit obstacle! 💥\n";
        }

        // Draw
        window.clear();
        player.draw(window);
        obstacleManager.draw(window);
        window.display();
    }

    return 0;
}
