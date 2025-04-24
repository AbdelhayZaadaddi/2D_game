#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Great Game");

    // Font loading
    sf::Font font;
    if (!font.loadFromFile("assets/font/CascadiaMono-Italic-VariableFont_wght.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }

    // Menu text buttons
    sf::Text startText("Start", font, 50);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(300, 200);

    sf::Text exitText("Exit", font, 50);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(300, 300);

    // Background (optional)
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/img/bg.jpeg")) {
        std::cout << "Background not found!" << std::endl;
    }
    sf::Sprite bgSprite(bgTexture);

    // Player setup
    sf::Texture playerText;
    if (!playerText.loadFromFile("assets/img/plr.png")) {
        std::cout << "Can't load the player texture" << std::endl;
        return -1;
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerText);
    playerSprite.setPosition(10, 10);
    float speed = 5.0f;

    // Obstacle
    sf::RectangleShape obstacle(sf::Vector2f(100, 100));
    obstacle.setFillColor(sf::Color::Red);
    obstacle.setPosition(400, 300);

    // Camera setup
    sf::View view(sf::FloatRect(0, 0, 800, 600));

    // Game states
    bool inGame = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

        if (!inGame) {
            // Handle hover color
            startText.setFillColor(startText.getGlobalBounds().contains(worldMousePos) ? sf::Color::Red : sf::Color::White);
            exitText.setFillColor(exitText.getGlobalBounds().contains(worldMousePos) ? sf::Color::Red : sf::Color::White);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (startText.getGlobalBounds().contains(worldMousePos)) {
                    std::cout << "Start Game!" << std::endl;
                    inGame = true;
                }
                if (exitText.getGlobalBounds().contains(worldMousePos)) {
                    window.close();
                }
            }
        }

        if (inGame) {
            // Movement input
            sf::Vector2f movement(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;

            sf::Vector2f newPosition = playerSprite.getPosition() + movement;

            // Boundary check
            if (newPosition.x >= 0 && newPosition.y >= 0 &&
                newPosition.x + playerSprite.getGlobalBounds().width <= window.getSize().x &&
                newPosition.y + playerSprite.getGlobalBounds().height <= window.getSize().y) {

                playerSprite.move(movement);

                if (playerSprite.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
                    playerSprite.move(-movement);
                    std::cout << "Collision detected!" << std::endl;
                }
            }

            view.setCenter(playerSprite.getPosition());
            window.setView(view);
        } else {
            window.setView(window.getDefaultView()); // Reset camera for menu
        }

        // Draw everything
        window.clear();
        if (inGame) {
            window.draw(bgSprite);
            window.draw(obstacle);
            window.draw(playerSprite);
        } else {
            window.draw(startText);
            window.draw(exitText);
        }
        window.display();
    }

    return 0;
}
