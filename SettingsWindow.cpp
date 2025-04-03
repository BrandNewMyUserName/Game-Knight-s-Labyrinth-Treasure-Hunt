#include "SettingsWindow.h"
#include "GameSettings.h"
#include "ScreenType.h"
#include <windows.h>

SettingsWindow::SettingsWindow() {

}

void SettingsWindow::draw(sf::RenderWindow& window, ScreenType& currentScreen) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    GameSettings& settings = GameSettings::getInstance();
    std::vector<sf::String> titles = { L"Режим гри", L"Ігрова мапа" };
    std::vector<sf::String> modeOptions = { L"Користувацький", L"A*", L"BFS" };
    std::vector<sf::String> sizeOptions = { L"Мала", L"Середня", L"Велика" };

    sf::Font font;
    font.loadFromFile("Fonts/troika.otf");

    sf::Text mainTitle;
    mainTitle.setFont(font);
    mainTitle.setFillColor(sf::Color::Color(177, 164, 122)); 
    mainTitle.setStyle(sf::Text::Bold);
    mainTitle.setString(L"Налаштування");
    mainTitle.setCharacterSize(90);
    mainTitle.setPosition(650.0f, 50.0f); 

    float menux = 650.0f;
    float menuy = 400.0f;
    int sizeFont = 50;
    int step = 100;

    ControlMenu gameModeMenu(window, menux, menuy, sizeFont, step, modeOptions);
    gameModeMenu.setPositionMenu(2);
    ControlMenu sizeMapMenu(window, menux + 500.0f, menuy, sizeFont, step, sizeOptions);
    sizeMapMenu.setPositionMenu(2);
    bool currentMenu = 0;

 
    sf::Text gameModeTitle;
    gameModeTitle.setFont(font);
    gameModeTitle.setFillColor(sf::Color::Color(236, 233, 218));
    gameModeTitle.setStyle(sf::Text::Bold);
    gameModeTitle.setString(titles[0]);
    gameModeTitle.setCharacterSize(70);
    gameModeTitle.setPosition(menux - 170.0f, menuy - step);

    sf::Text sizeMapTitle;
    sizeMapTitle.setFont(font);
    sizeMapTitle.setFillColor(sf::Color::Color(236, 233, 218)); 
    sizeMapTitle.setStyle(sf::Text::Bold);
    sizeMapTitle.setString(titles[1]);
    sizeMapTitle.setCharacterSize(70);
    sizeMapTitle.setPosition(menux + 320.0f, menuy - step);

    

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                currentScreen = ScreenMainMenu;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    if (!currentMenu)
                        gameModeMenu.navigateDown();
                    else
                        sizeMapMenu.navigateDown();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    if (!currentMenu)
                        gameModeMenu.navigateUp();
                    else
                        sizeMapMenu.navigateUp();
                }

                if (event.key.code == sf::Keyboard::Left) {
                    currentMenu = 0;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    currentMenu = 1;
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    if (!currentMenu) {
                        settings.setAlgorithm(gameModeMenu.getSelectedIndex());
                    }
                    if (currentMenu) {
                        settings.setLevel(sizeMapMenu.getSelectedIndex());
                    }
                }
            }
        }

        window.clear();
        window.draw(mainTitle);   
        window.draw(gameModeTitle); 
        window.draw(sizeMapTitle);  
        gameModeMenu.draw();
        sizeMapMenu.draw();
        window.display();
    }
}
