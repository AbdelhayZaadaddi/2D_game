#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Obstacle {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape fallbackShape;
    bool textureLoaded = false;

public:
    // path + spawn coords
    Obstacle(const std::string& texturePath, float startX, float startY);

    // slide left
    void update(float dx);

    // draw either sprite or red rect
    void draw(sf::RenderWindow& window) const;

    // used for collision
    sf::FloatRect getGlobalBounds() const;

    // used for off‐screen culling
    float getX() const;
};

#endif // OBSTACLE_HPP
