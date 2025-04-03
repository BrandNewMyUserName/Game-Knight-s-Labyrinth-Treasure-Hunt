#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class GameController {
public:
    GameController(Map& map, bool autoMode);

    void setPlayerView(sf::View& view, float x, float y);
    void handleAutoMode(Character& character, float& CurrentFrame);
    void handleUserMode(Character& character, float& CurrentFrame);
    void updateGame(sf::RenderWindow& window, sf::View& view, Character& character, const Map& GameMap, const int HEIGHT_MAP, const int WIDTH_MAP, const int PICTURE_RESOLUTION, sf::Text& scoreValue, sf::Text& pos);
    void drawMap(sf::RenderWindow& window, const Map& GameMap, const int HEIGHT_MAP, const int WIDTH_MAP, const int PICTURE_RESOLUTION);

private:
    bool autoMode;
    bool startProcess;
    bool MakePause;
};
