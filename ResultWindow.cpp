#include "ResultWindow.h"
#include "ScreenType.h"
#include <string>

ResultWindow::ResultWindow() {
    scoreValue = 0;
    gameTime = 0;
}

void ResultWindow::initVar(GameResult& sessionResults) {

    this->scoreValue = sessionResults.getScore();
    this->gameTime = sessionResults.getTime();
}

void ResultWindow::draw(sf::RenderWindow& window, ScreenType& currentScreen) {
    sf::Font font;
    font.loadFromFile("Fonts/troika.otf"); 

    // Заголовок
    sf::Text mainTitle;
    mainTitle.setFont(font);
    mainTitle.setFillColor(sf::Color::Color(177, 164, 122));
    mainTitle.setString(L"Результати гри");
    mainTitle.setCharacterSize(70);
    mainTitle.setPosition(700.0f, 50.0f);
    

    // Кількість зібраних монет
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(L"Зібрано монет: " + std::to_wstring(scoreValue));
    scoreText.setCharacterSize(60);
    scoreText.setPosition(500.0f, 250.0f);

    // Витрачений час
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setFillColor(sf::Color::White);
    int seconds = gameTime / 1e6;
    int miliseconds = (gameTime - seconds) / 1000;
    timeText.setString(L"Витрачений час: " + std::to_wstring(seconds) + L"." + std::to_wstring(miliseconds) + L" секунд");
    timeText.setCharacterSize(60);
    timeText.setPosition(500.0f, 350.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                currentScreen = ScreenMainMenu;
                window.close();
            }
        }

        window.clear();
        window.draw(mainTitle);   // Намалювати заголовок
        window.draw(scoreText);   // Намалювати кількість зібраних монет
        window.draw(timeText);    // Намалювати витрачений час
        window.display();
    }
}
