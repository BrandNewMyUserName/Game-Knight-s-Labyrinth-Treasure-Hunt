//#include "ExtendMenu.h"
//
//
//ExtendMenu::ExtendMenu(sf::RenderWindow& window, float menux, float menuy, int sizeFont, int step, std::vector<std::vector<sf::String>>& menuItems, std::vector<sf::String>& titles)
//    : mywindow(window), currentMenu(0)
//{
//    menus = new ControlMenu[menuItems.size()];
//    for (int i = 0; i < menuItems.size(); i++) {
//        menus[i] = new ControlMenu(window, menux, menuy, sizeFont, step, menuItems[i], titles[i]);
//    }
//}
//
//void ExtendMenu::MoveLeftMenu() {
//    if (currentMenu > 0) {
//        currentMenu--;
//    }
//    else {
//        currentMenu = menus.size() - 1;
//    }
//}
//
//void ExtendMenu::choosePoint() {
//
//    if (currentMenu > 0) {
//        currentMenu--;
//    }
//    else {
//        currentMenu = menus.size() - 1;
//    }
//}
//
//void ExtendMenu::MoveRightMenu() {
//
//    int item = menus[currentMenu].getSelectedIndex();
//
//
//    if (currentMenu < menus.size() - 1) {
//        currentMenu++;
//    }
//    else {
//        currentMenu = 0;
//    }
//
//
//}
//
//void ExtendMenu::draw() {
//    menus[currentMenu].draw();
//}
//
