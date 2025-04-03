#pragma once
#include "Map.h"
#include "SettingsWindow.h"
#include "GameWindow.h"

static class GameSettings {
private:

    static GameSettings& instance;
    bool autoMode;
    int pictureResolution ;
    int algorithm ;
    int level;

    GameSettings() {
        autoMode = false;
        pictureResolution = 120;
        algorithm = 0;
        level = 1;
    }

public:
    static GameSettings& getInstance();
    
    bool getMode() const;

    void setAlgorithm(int algoNum);
    int getAlgorithm() const;

    int getPictureResolution() const;

    int getLevel() const;
    void setLevel(int i);

    GameSettings(const GameSettings&);
    GameSettings& operator=(const GameSettings&);
};


