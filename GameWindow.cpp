#include "GameWindow.h"
#include "GameResult.h"
#include <chrono>
#include <thread>
#include "ScreenType.h"


GameWindow::GameWindow(GameResult &sessionResult) {
    this->sessionResult = &sessionResult;
}

void GameWindow::setPlayerView(float x, float y) {
    view.setCenter(x + 100, y);
}

void GameWindow::drawMap(RenderWindow& window, const Map& GameMap, const int& HEIGHT_MAP, const int& WIDTH_MAP, const int& PICTURE_RESOLUTION) {

    s_map.setTextureRect(IntRect(0, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));
    s_map.setPosition(0 * PICTURE_RESOLUTION, 0 * PICTURE_RESOLUTION);

    window.draw(s_map);

    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (GameMap.Grid[i][j] == 0)
                this->s_map.setTextureRect(IntRect(0 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Шляхи 
            if (GameMap.Grid[i][j] == 1)
                this->s_map.setTextureRect(IntRect(1 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Стіни
            if (GameMap.Grid[i][j] == 2)
                this->s_map.setTextureRect(IntRect(2 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Золото
            if (GameMap.Grid[i][j] == 5)
                this->s_map.setTextureRect(IntRect(3 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Скарбниця
            if (GameMap.Grid[i][j] == 4) 
                this->s_map.setTextureRect(IntRect(4 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Ключ
            if (GameMap.Grid[i][j] == 3)
                this->s_map.setTextureRect(IntRect(5 * PICTURE_RESOLUTION, 0, PICTURE_RESOLUTION, PICTURE_RESOLUTION));   // Двері

            // Розміщення поля згідно позиції
            s_map.setPosition(j * PICTURE_RESOLUTION, i * PICTURE_RESOLUTION);
            window.draw(s_map);
        }
    }
}

void GameWindow::draw(RenderWindow& window, ScreenType& currentScreen) {
    Texture mapTexture;
    Image mapImage;
    mapImage.loadFromFile("pictures/map(120x120)_3.jpg");
    mapTexture.loadFromImage(mapImage);
    s_map.setTexture(mapTexture);

    ////Ініціалізація елементів гри
    GameSettings& settings = GameSettings::getInstance();
    Map GameMap(settings.getLevel());
    const int HEIGHT_MAP = GameMap.Grid.size();
    const int WIDTH_MAP = GameMap.Grid[0].size();
    const int PICTURE_RESOLUTION = settings.getPictureResolution();
    autoMode = settings.getMode();
    Character character(GameMap, autoMode);


    ////Встановлення  
    view.reset(FloatRect(character.x, character.y, 800, 450));
    setPlayerView(character.x, character.y);

    Font font;
    font.loadFromFile("Fonts/troika.otf");
    Text scoreValue(" ", font, 100);
    scoreValue.setStyle(Text::Italic);
    scoreValue.setFillColor(Color::Black);

    Text pos(" ", font, 100);
    pos.setStyle(Text::Italic);
    pos.setFillColor(Color::Black);

    float CurrentFrame = 0;


    bool startSearch = 0;
    int algorithm = settings.getAlgorithm();
    bool startProccess = 0;

     Clock clock;
     while (window.isOpen()) {
     sf::Event event;

     while (window.pollEvent(event)) {

         if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
             currentScreen = ScreenMainMenu;
             window.close();
         }
     }

     if (character.IsTreasureOpened) {
         float GameTime = clock.getElapsedTime().asMicroseconds();
         sessionResult->loadResults(character.playerScore, GameTime);
         currentScreen = ScreenResults;
         window.close();
     }

     if (autoMode) {

         if (startProccess) {
             character.autoMove(CurrentFrame, startProccess);
             setPlayerView(character.x, character.y);
         }
             
         if (!startProccess) {
             startProccess = 1;
             character.layPath(algorithm);
             character.placeInAngle();
         }

     }

     if (!autoMode) {
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
             character.toMove(CurrentFrame, autoMode);
             setPlayerView(character.x, character.y);
         }
     }

     window.setView(view);
     window.clear(Color(59, 62, 39));
     drawMap(window, GameMap, HEIGHT_MAP, WIDTH_MAP, PICTURE_RESOLUTION);

     std::ostringstream currentScore;
     currentScore << character.playerScore;
     scoreValue.setString(L"Зібрано монет: " + currentScore.str());
     scoreValue.setPosition(view.getCenter().x + 250, view.getCenter().y - 200);
     scoreValue.setCharacterSize(12);

     window.draw(scoreValue);
     window.draw(pos);
     window.draw(character.characterSprite);
     window.display();

 }

}
