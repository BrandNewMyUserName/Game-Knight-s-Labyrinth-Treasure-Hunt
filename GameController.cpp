#include "GameController.h"

GameController::GameController(Map& map, bool autoMode)
    : autoMode(autoMode), startProcess(false), MakePause(false) {}

void GameController::setPlayerView(sf::View& view, float x, float y) {
    view.setCenter(x + 100, y);
}

void GameController::handleAutoMode(Character& character, float& CurrentFrame) {
    if (!startProcess) {
        character.layPath();
        character.placeInAngle();
        startProcess = true;
    }

    character.autoMove(CurrentFrame, autoMode);
    setPlayerView(view, character.x, character.y);

    if (autoMode) {
        autoMode = true;
        MakePause = true;
    }
}

void GameController::handleUserMode(Character& character, float& CurrentFrame) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        character.toMove(CurrentFrame, autoMode);
        setPlayerView(view, character.x, character.y);
    }
}

void GameController::updateGame(sf::RenderWindow& window, sf::View& view, Character& character, const Map& GameMap, const int HEIGHT_MAP, const int WIDTH_MAP, const int PICTURE_RESOLUTION, sf::Text& scoreValue, sf::Text& pos) {
    sf::Clock clock;
    float CurrentFrame = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (character.IsTreasureOpened) {
            window.close();
        }

        if (autoMode) {
            handleAutoMode(character, CurrentFrame);
        }
        else {
            handleUserMode(character, CurrentFrame);
        }

        window.setView(view);
        window.clear(sf::Color(59, 62, 39));
        drawMap(window, GameMap, HEIGHT_MAP, WIDTH_MAP, PICTURE_RESOLUTION);

        std::ostringstream currentScore;
        std::ostringstream Pos_X_str, Pos_Y_str;
        Pos_X_str << character.x_pos;
        Pos_Y_str << character.y_pos;
        currentScore << character.playerScore;
        scoreValue.setString(L"Зібрано монет: " + currentScore.str());
        scoreValue.setPosition(view.getCenter().x + 250, view.getCenter().y - 200);
        scoreValue.setCharacterSize(12);

        pos.setString(Pos_X_str.str() + "  Pos_y: " + Pos_Y_str.str());
        pos.setPosition(view.getCenter().x + 250, view.getCenter().y - 100);
        pos.setCharacterSize(12);

        window.draw(scoreValue);
        window.draw(pos);
        window.draw(character.characterSprite);
        window.display();

        if (MakePause) {
            std::this_thread::sleep_for(std::chrono::microseconds(1200));
            MakePause = false;
        }
    }
}

void GameController::drawMap(sf::RenderWindow& window, const Map& GameMap, const int HEIGHT_MAP, const int WIDTH_MAP, const int PICTURE_RESOLUTION) {
    sf::Sprite s_map;
    s_map.setTextureRect(sf::IntRect(0, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));
    s_map.setPosition(0 * PICTURE_RESOLUTION, 0 * PICTURE_RESOLUTION);

    window.draw(s_map);

    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (GameMap.Grid[i][j] == ' ')
                s_map.setTextureRect(sf::IntRect(0 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Шляхи 
            if (GameMap.Grid[i][j] == '0')
                s_map.setTextureRect(sf::IntRect(1 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Стіни
            if (GameMap.Grid[i][j] == 'c')
                s_map.setTextureRect(sf::IntRect(2 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Золото
            if (GameMap.Grid[i][j] == 't')
                s_map.setTextureRect(sf::IntRect(3 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Скарбниця
            if (GameMap.Grid[i][j] == 'k')
                s_map.setTextureRect(sf::IntRect(4 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Ключ
            if (GameMap.Grid[i][j] == 'd')
                s_map.setTextureRect(sf::IntRect(5 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Двері

            // Розміщення поля згідно позиції
            s_map.setPosition(j * PICTURE_RESOLUTION, i * PICTURE_RESOLUTION);
            window.draw(s_map);
        }
    }
}
