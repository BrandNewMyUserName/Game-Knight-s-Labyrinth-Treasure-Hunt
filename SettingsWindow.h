#pragma once
#include "Screen.h"
#include "ControlMenu.h"
#include "GameSettings.h"

class SettingsWindow : public Screen
{
public:
    SettingsWindow();

    void draw(sf::RenderWindow& window, ScreenType& currentScreen);

};

