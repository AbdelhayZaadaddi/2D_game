#include "Obstacle.hpp"

Obstacle::Obstacle(const std::string& texturePath, float startX, float startY) {
    if (texture.loadFromFile(texturePath)) {
        textureLoaded = true;
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
    } else {
        std::cerr << "⚠️  Failed to load obstacle texture: " 
                  << texturePath << "\n";
        textureLoaded = false;
        // make a 50×50 red block (adjust size as you like)
        fallbackShape.setSize({50.f, 50.f});
        fallbackShape.setFillColor(sf::Color::Red);
        fallbackShape.setPosition(startX, startY);
    }
}

void Obstacle::update(float dx) {
    if (textureLoaded)
        sprite.move(-dx, 0.f);
    else
        fallbackShape.move(-dx, 0.f);
}

void Obstacle::draw(sf::RenderWindow& window) const {
    if (textureLoaded)
        window.draw(sprite);
    else
        window.draw(fallbackShape);
}

sf::FloatRect Obstacle::getGlobalBounds() const {
    return textureLoaded 
         ? sprite.getGlobalBounds() 
         : fallbackShape.getGlobalBounds();
}

float Obstacle::getX() const {
    return textureLoaded 
         ? sprite.getPosition().x 
         : fallbackShape.getPosition().x;
}
