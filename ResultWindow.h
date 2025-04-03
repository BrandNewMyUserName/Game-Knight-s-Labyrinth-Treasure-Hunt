#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "GameResult.h"

class ResultWindow : public Screen {
private:
    int scoreValue;
    float gameTime;
public:
    ResultWindow();
    void initVar(GameResult& sessionResults);
    void draw(sf::RenderWindow& window, ScreenType& currentScreen);
};
