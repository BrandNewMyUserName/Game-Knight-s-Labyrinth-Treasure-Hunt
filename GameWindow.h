#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Map.h"
#include "Screen.h"
#include "GameSettings.h"
#include "GameResult.h"
#include "AStar.h"
#include "Bfs.h"

#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class GameWindow: Screen {
private:
    View view;
    Sprite s_map;
    bool autoMode;
    int algorithm;
    GameResult *sessionResult;

public:
    GameWindow(GameResult &sessionResult);
    void setPlayerView(float x, float y);
    void draw(RenderWindow& window, ScreenType& currentScreen);
    void drawMap(RenderWindow& window, const Map &GameMap, const int& HEIGHT_MAP, const int& WIDTH_MAP, const int& PICTURE_RESOLUTION);

    friend class Character;
};

