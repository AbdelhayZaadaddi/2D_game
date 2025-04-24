#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        float speed = 0.9f;

    public:
        Player(const std::string& texturePath);
        void handleInput();
        void update(const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;
};

#endif