#include "Background.hpp"

Background::Background(const std::string& texturePath){
    if (!texture.loadFromFile(texturePath)){
        std::cerr << "Can't load the background texture from " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
}

void Background::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void Background::setPoisition(const sf::Vector2f& position){
    sprite.setPosition(position);
}