#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacle.hpp"

#include <vector>
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time
#include <algorithm> // std::remove_if

int main(){
    sf::RenderWindow window({800,600}, "Bike Game");
    Player player("assets/img/bik.png");

    // seed random for obstacle Y
    std::srand((unsigned)std::time(nullptr));

    std::vector<Obstacle> obstacles;
    sf::Clock spawnClock;

    const float obstacleSpeed = 0.1f;      // pixels per frame
    const float spawnInterval  = 2.0f;    // seconds

    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt))
            if(evt.type == sf::Event::Closed)
                window.close();

        // 1) spawn new obstacle every spawnInterval seconds
        if(spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
            // pick a random Y so the whole sprite stays on-screen
            // we need a temporary Obstacle to get its height:
            Obstacle temp("assets/img/bg.jpeg", 0, 0);
            float maxY = window.getSize().y - temp.getGlobalBounds().height;
            float y = static_cast<float>(std::rand()) / RAND_MAX * maxY;
            // spawn just off the right edge:
            float startX = window.getSize().x + 10.f;
            obstacles.emplace_back("assets/img/bg.jpegng", startX, y);

            spawnClock.restart();
        }

        // 2) input + player update
        player.handleInput();
        player.update(window);

        // 3) move & draw everything
        window.clear();

        // draw player behind obstacles if you like, or vice-versa:
        player.draw(window);

        for(auto& obs : obstacles) {
            obs.update(obstacleSpeed);
            obs.draw(window);

            // 4) collision test
            if (player.getGlobalBounds().intersects(obs.getGlobalBounds())) {
                std::cout << "💥 Hit obstacle! 💥\n";
            }
        }

        // optional: remove off-screen obstacles
        obstacles.erase(
            std::remove_if(obstacles.begin(),
                           obstacles.end(),
                           [&](const Obstacle& o){
                               return o.getX() + o.getGlobalBounds().width < 0;
                           }),
            obstacles.end());

        window.display();
    }

    return 0;
}
