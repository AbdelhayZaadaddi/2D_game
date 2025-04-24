#include "Player.hpp"

Player::Player(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Can't load the player texture from " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(150, 100);
    sprite.setScale(0.3f, 0.3f);
    sprite.setRotation(90.f);
}

void Player::handleInput(){
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed;

   /*  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed; */

    // ← actually move the sprite
    sprite.move(movement);
}

void Player::update(const sf::RenderWindow& window){
    sf::Vector2f position = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    float winW = static_cast<float>(window.getSize().x);
    float winH = static_cast<float>(window.getSize().y);

    if (position.x < 0) {
        position.x = 0;
    } else if (position.x + bounds.width > winW) {
        position.x = winW - bounds.width;
    }
    if (position.y < 0) {
        position.y = 0;
    } else if (position.y + bounds.height > winH) {
        position.y = winH - bounds.height;
    }
    sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
