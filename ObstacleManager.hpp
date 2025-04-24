#ifndef OBSTACLE_MANAGER_HPP
#define OBSTACLE_MANAGER_HPP

#include "Obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

class ObstacleManager {
private:
    std::vector<Obstacle> obstacles;
    sf::Clock spawnClock;
    float spawnInterval;
    float obstacleSpeed;

public:
    ObstacleManager(float spawnInterval, float obstacleSpeed);

    // Update all obstacles and spawn new ones if needed
    void update(sf::RenderWindow& window);

    // Draw all obstacles
    void draw(sf::RenderWindow& window) const;

    // Check for collisions with the player
    bool checkCollision(const sf::FloatRect& playerBounds) const;
};

#endif