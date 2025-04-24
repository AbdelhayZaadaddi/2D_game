#include "ObstacleManager.hpp"

ObstacleManager::ObstacleManager(float spawnInterval, float obstacleSpeed)
    : spawnInterval(spawnInterval), obstacleSpeed(obstacleSpeed) {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random generator
}

void ObstacleManager::update(sf::RenderWindow& window) {
    // Spawn new obstacle if needed
    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        Obstacle temp("assets/obstacle/obs2.png", 0, 0);
        float maxY = window.getSize().y - temp.getGlobalBounds().height;
        float y = static_cast<float>(std::rand()) / RAND_MAX * maxY;
        float startX = window.getSize().x + 10.f;
        obstacles.emplace_back("assets/obstacle/obs2.png", startX, y);
        spawnClock.restart();
    }

    // Update all obstacles
    for (auto& obs : obstacles) {
        obs.update(obstacleSpeed);
    }

    // Remove off-screen obstacles
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(),
                       [&](const Obstacle& o) {
                           return o.getX() + o.getGlobalBounds().width < 0;
                       }),
        obstacles.end());
}

void ObstacleManager::draw(sf::RenderWindow& window) const {
    for (const auto& obs : obstacles) {
        obs.draw(window);
    }
}

bool ObstacleManager::checkCollision(const sf::FloatRect& playerBounds) const {
    for (const auto& obs : obstacles) {
        if (playerBounds.intersects(obs.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}