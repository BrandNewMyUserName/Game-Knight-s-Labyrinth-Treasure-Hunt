#include "MainWindow.h"

MainWindow::MainWindow() : IsRunning(1) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    font.loadFromFile("Fonts/troika.otf");

    title.setFont(font);
    title.setString(L"Лабіринт лицаря: Пошук скарбів");
    title.setCharacterSize(70);
    title.setFillColor(Color::Color(177, 164, 122));
    title.setStyle(Text::Bold);

    backgroundTexture.loadFromFile("Pictures/MainWind-background.png");
    backgroundSprite.setTexture(backgroundTexture);
}

bool MainWindow::getState() {
    return IsRunning;
}

void MainWindow::scaleBackground(sf::RenderWindow & window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);
}

void MainWindow::centerTitle(sf::RenderWindow& window) {
    sf::FloatRect textRect = title.getLocalBounds();
    title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 5.0f);
    title.setPosition(window.getSize().x / 2.0f, textRect.height);
}

void MainWindow::draw(sf::RenderWindow& window, ScreenType& currentScreen) {
    std::vector<sf::String> menuItems = { L"Почати гру", L"Налаштування", L"Вийти" };
    sf::String Title = L"Лабіринт лицаря: Пошук скарбів";
    ControlMenu mainMenu(window, 1100.0f, 200.0f, 60, 100, menuItems);
    mainMenu.setPositionMenu(3);

    scaleBackground(window);
    centerTitle(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                IsRunning = 0;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    mainMenu.navigateUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    mainMenu.navigateDown();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    int select = mainMenu.getSelectedIndex();
                    if (select == 0) {
                        currentScreen = ScreenGame;
                        window.close();
                    }
                    if (select == 1) {
                        currentScreen = ScreenSettings;
                        window.close();
                    }
                    if (select == 2) {
                        IsRunning = 0;
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        mainMenu.draw();
        window.display();
    }
}