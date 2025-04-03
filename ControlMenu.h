#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class ControlMenu
{
    float menuXPosition;
    float menuYPosition;
    int menuStep;
    int maxMenuItems;
    int fontSize;
    int selectedMenuItem;
    sf::Font font;
    std::vector<sf::Text> menuItems;

    sf::Color menuTextColor = sf::Color::White;
    sf::Color selectedTextColor = sf::Color::Yellow;
    sf::Color borderColor = sf::Color::Black;
    sf::RenderWindow& window;

    void initializeText(sf::Text& text, const sf::String& str, float xpos, float ypos) const;

public:

    ControlMenu(sf::RenderWindow& window, float menuX, float menuY, int fontSize, int step, std::vector<sf::String>& names);

    void draw();

    void navigateUp();

    void navigateDown();

    void setMenuTextColors(sf::Color menuColor, sf::Color selectedColor, sf::Color borderColor);

    void setPositionMenu(int posX);

    int getSelectedIndex() const;

};
