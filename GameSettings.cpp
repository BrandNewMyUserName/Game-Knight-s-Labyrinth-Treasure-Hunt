#include "GameSettings.h"

GameSettings& GameSettings::getInstance() {
    static GameSettings instance;
    return instance;
}


bool GameSettings::getMode() const {
    return autoMode;
}

void GameSettings::setAlgorithm(int algoNum) {
    algorithm = algoNum;

    if (!algorithm)
        autoMode = 0;
    else
        autoMode = 1;
}

int GameSettings::getAlgorithm() const {
    return algorithm;
}

int GameSettings::getLevel() const {
    return level;
}


void GameSettings::setLevel(int i)
{
    level = i;
}

int GameSettings::getPictureResolution() const {
    return pictureResolution;
}
