#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Background {
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    public:
        explicit Background(const std::string& texturePath);

        void draw(sf::RenderWindow& window);

        void setPoisition(const sf::Vector2f& position);
};

#endif