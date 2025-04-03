#include "Character.h"
#include "GameSettings.h"

Character::Character(Map& map, bool & autoMode) : x_pos(1), y_pos(1), h(74), w(75), speedMove(0.03), speedRun(1), dir(0), dx(1), dy(0), MAP(map), HEIGHT_MAP(MAP.Grid.size()), WIDTH_MAP(MAP.Grid[0].size()), PICTURE_RESOLUTION(120) {
    playerScore = 0, HasKey = 0,  IsTreasureOpened = 0, this->autoMode = autoMode;
    x = 0, y = 0;
    
    characterImage.loadFromFile("pictures/Knight_spikes.png" );
    characterTexture.loadFromImage(characterImage);
    characterSprite.setTexture(characterTexture);
    characterSprite.setTextureRect(IntRect(8, 15, 180, 112));
    setMapPos();
    characterSprite.setPosition(x, y);
}

void Character::setMapPos() {
    x = x_pos * PICTURE_RESOLUTION;
    y = y_pos * PICTURE_RESOLUTION;
}

void Character::layPath(int algorithm) {
    if (algorithm == 1) {
        AStar AStarnavigation(MAP.Grid, HasKey);
        if (AStarnavigation.search(x_pos, y_pos))
            path = AStarnavigation.backPath();
    }

    if (algorithm == 2) {
        BFS Bfsnavigation(MAP.Grid, HasKey);
        if (Bfsnavigation.search(x_pos, y_pos))
            path = Bfsnavigation.backPath();
    }
 
}

void Character::autoMove(float& CurrentFrame, bool &startProccess) {
    pair<int, int> nextPos = path.front();

    if ((x - nextPos.second * PICTURE_RESOLUTION) == 0 && (y - nextPos.first * PICTURE_RESOLUTION) == 0) {
        path.erase(path.begin());
        if (!path.empty())
            nextPos = path.front();
        else {
            startProccess = 0;
            return;
        }
    }

    int pix_dist_x = nextPos.second * PICTURE_RESOLUTION - x;
    int pix_dist_y = nextPos.first * PICTURE_RESOLUTION - y;

    setDir(pix_dist_x, pix_dist_y);

    autoChangeSpike(CurrentFrame);

    setDirection();
    update(autoMode);

}

void Character::autoChangeSpike(float& CurrentFrame) {
    int coordinates[3][3] = {
        {76, 250, 430},
        {25, 210, 400},
        {66, 250, 435}
    };

    switch (dir) {
    case 0:
        CurrentFrame += speedMove;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[0][static_cast<int>(CurrentFrame)], 25, 75, 74));
        break;
    case 1:
        CurrentFrame += speedMove;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(600, coordinates[1][static_cast<int>(CurrentFrame)], 75, 74));
        break;
    case 2:
        CurrentFrame += speedMove;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[0][static_cast<int>(CurrentFrame)], 400, 75, 74));
        break;
    case 3:
        CurrentFrame += speedMove;
        if (CurrentFrame > 3) CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[2][static_cast<int>(CurrentFrame)], 210, 75, 74));
        break;
    }
}

void Character::placeInAngle() {
    characterSprite.setPosition(y_pos * PICTURE_RESOLUTION, x_pos * PICTURE_RESOLUTION);
    y = y_pos * PICTURE_RESOLUTION;
    x = x_pos * PICTURE_RESOLUTION;
}

void Character::getGridPos() {
    x_pos = x / PICTURE_RESOLUTION;
    y_pos = y / PICTURE_RESOLUTION;
}

void Character::setDir(int dir_x, int dir_y) {

    if (dir_x == 0) {
        if (dir_y > 0)
            dir = 3;
        if (dir_y < 0)
            dir = 1;
    }
    else {
        if (dir_x > 0)
            dir = 0;
        if (dir_x < 0)
            dir = 2;
    }
}

void Character::setDirection() {
    switch (dir) {
    case 0:
        dx = speedRun;
        dy = 0;
        break;
    case 1:
        dx = 0;
        dy = -speedRun;
        break;
    case 2:
        dx = -speedRun;
        dy = 0;
        break;
    case 3:
        dx = 0;
        dy = speedRun;
        break;
    }
}

void Character::update(bool autoMode) {
    x += dx;
    y += dy;
    characterSprite.setPosition(x, y);
    interactionWithMap();
    getGridPos();
}

void Character::interactionWithMap() {
    for (int i = y / PICTURE_RESOLUTION; i < (y + h) / PICTURE_RESOLUTION; i++)
        for (int j = x / PICTURE_RESOLUTION; j < (x + w) / PICTURE_RESOLUTION; j++) {
            if (MAP.Grid[i][j] == 1 || (MAP.Grid[i][j] == 3 && !HasKey) || (MAP.Grid[i][j] == 5 && !HasKey)) {
                switch (dir) {
                case 0: x = j * PICTURE_RESOLUTION - w; break;
                case 1: y = i * PICTURE_RESOLUTION + PICTURE_RESOLUTION; break;
                case 2: x = j * PICTURE_RESOLUTION + PICTURE_RESOLUTION; break;
                case 3: y = i * PICTURE_RESOLUTION - h; break;
                }
            }

            if (MAP.Grid[i][j] == 4) {
                HasKey = 1;
                MAP.Grid[i][j] = 0;
            }

            if (MAP.Grid[i][j] == 2) {
                ++playerScore;
                MAP.Grid[i][j] = 0;
            }

            if (MAP.Grid[i][j] == 5 && HasKey) {
                IsTreasureOpened = 1;
            }


        }
}

void Character::toMove(float& CurrentFrame, bool& autoMode) {
    int coordinates[3][3] = {
        {67, 250, 430},
        {25, 210, 400},
        {66, 250, 435}
    };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        CurrentFrame += speedMove ;
        if (CurrentFrame > 3)
            CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[0][int(CurrentFrame)], 400, 75, 74));
        dir = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        CurrentFrame += speedMove;
        if (CurrentFrame > 3)
            CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(600, coordinates[1][int(CurrentFrame)], 75, 74));
        dir = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        CurrentFrame += speedMove;
        if (CurrentFrame > 3)
            CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[2][int(CurrentFrame)], 200, 75, 74));
        dir = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        CurrentFrame += speedMove;
        if (CurrentFrame > 3)
            CurrentFrame -= 3;
        characterSprite.setTextureRect(IntRect(coordinates[0][int(CurrentFrame)], 25, 75, 74));
        dir = 0;
    }

    setDirection();
    update(autoMode);
}
