#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include "Screen.h"
#include "ControlMenu.h"

using namespace std;
using namespace sf;

class MainWindow : Screen
{
private:
    bool IsRunning;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Text title;
    Font font;

public:
    MainWindow();

    bool getState();

    void scaleBackground(sf::RenderWindow& window);

    void centerTitle(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window, ScreenType& currentScreen);
};
