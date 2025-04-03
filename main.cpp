#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "ScreenType.h"

#include "MainWindow.h"
#include "ResultWindow.h"
#include "SettingsWindow.h"
#include "GameResult.h"

#include "ControlMenu.h"
#include "GameSettings.h"


using namespace std;
using namespace sf;

GameSettings& settings = GameSettings::getInstance();

int main() {
    ScreenType currentScreen = ScreenMainMenu;
    MainWindow mainMenu;
    SettingsWindow settingsWind;
    GameResult sessionResults;
    GameWindow game(sessionResults);
    ResultWindow results;


    while (mainMenu.getState()) {
        RenderWindow window(VideoMode(1920, 1080), L"Ћицарь у лаб≥ринт≥: пошук скарб≥в");
        switch (currentScreen) {
        case ScreenMainMenu:
            mainMenu.draw(window, currentScreen);
            break;
        case ScreenGame:
            sessionResults.reloadResults();
            game.draw(window, currentScreen);
            break;
        case ScreenSettings:
            settingsWind.draw(window, currentScreen);
            break;
        case ScreenResults:
            results.initVar(sessionResults);
            results.draw(window, currentScreen);
            break;
        }
    }

    return 0;
}
