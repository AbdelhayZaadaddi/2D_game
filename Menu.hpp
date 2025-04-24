#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
    private:
        sf::RenderWindow& window;
        sf::Font font;
        sf::Text menuItems[2];
        int selected;
    
        
    public:
        Menu(sf::RenderWindow& window);
        int displayMenu();

    

};

#endif