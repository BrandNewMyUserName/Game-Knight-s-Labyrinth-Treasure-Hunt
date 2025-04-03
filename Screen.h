#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenType.h"



class Screen {
public:
    virtual void draw(sf::RenderWindow& window, ScreenType& currentScreen) = 0;
};