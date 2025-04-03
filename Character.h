#pragma once
#include "Astar.h"
#include "Bfs.h"
#include "Map.h"
#include "GameSettings.h"
#include <cmath>
#include <algorithm>

class Character {
public:
    float x, y, speedMove, speedRun, h, w, dx, dy;
    int x_pos, y_pos, dir, playerScore;
    bool HasKey, autoMode, IsTreasureOpened;
    String Picture_name;
    Image characterImage;
    Texture characterTexture;
    Sprite characterSprite;
    Map &MAP;
    vector<pair<int, int>> path;
    const int PICTURE_RESOLUTION;
    const int &HEIGHT_MAP;
    const int &WIDTH_MAP;
    
    Character(Map& map, bool & autoMode);

    void setMapPos();

    void layPath(int algorithm);

    void autoMove(float& CurrentFrame, bool& startProccess);

    void autoChangeSpike(float& CurrentFrame);

    void placeInAngle();

    void getGridPos();

    void setDir(int dir_x, int dir_y);

    void setDirection();

    void update(bool autoMode);

    void interactionWithMap();

    void toMove(float& CurrentFrame, bool& autoMode);


};

