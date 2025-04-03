#include "ControlMenu.h"

ControlMenu::ControlMenu(sf::RenderWindow& window, float menuX, float menuY, int fontSize, int step, std::vector<sf::String>& names)
    : window(window), menuXPosition(menuX), menuYPosition(menuY), menuStep(step), maxMenuItems(static_cast<int>(names.size())), fontSize(fontSize), menuItems(names.size())
{
    font.loadFromFile("Fonts/troika.otf");
    setMenuTextColors(sf::Color::White, sf::Color::Red, sf::Color::Black);

    for (int i = 0, ypos = static_cast<int>(menuYPosition); i < maxMenuItems; i++, ypos += menuStep)
        initializeText(menuItems[i], names[i], menuXPosition, static_cast<float>(ypos));

    selectedMenuItem = 0;
    menuItems[selectedMenuItem].setFillColor(selectedTextColor);
}

void ControlMenu::initializeText(sf::Text& text, const sf::String& str, float xpos, float ypos) const
{
    text.setFont(font);
    text.setFillColor(menuTextColor);
    text.setString(str);
    text.setCharacterSize(fontSize);
    text.setPosition(xpos, ypos);
    text.setOutlineThickness(3);
    text.setOutlineColor(borderColor);
}

void ControlMenu::setPositionMenu(int posX)
{
    float nullx = 0;
    for (int i = 0; i < maxMenuItems; i++) {
        switch (posX)
        {
        case 0:
            nullx = 0;
            break;
        case 1:
            nullx = menuItems[i].getLocalBounds().width;
            break;
        case 2:
            nullx = menuItems[i].getLocalBounds().width / 2;
            break;
        default: break;
        }
        menuItems[i].setPosition(menuItems[i].getPosition().x - nullx, menuItems[i].getPosition().y);
    }
}

void ControlMenu::navigateUp()
{
    selectedMenuItem--;
    if (selectedMenuItem >= 0) {
        menuItems[selectedMenuItem].setFillColor(selectedTextColor);
        menuItems[selectedMenuItem + 1].setFillColor(menuTextColor);
    }
    else {
        menuItems[0].setFillColor(menuTextColor);
        selectedMenuItem = maxMenuItems - 1;
        menuItems[selectedMenuItem].setFillColor(selectedTextColor);
    }
}

void ControlMenu::navigateDown()
{
    selectedMenuItem++;
    if (selectedMenuItem < maxMenuItems) {
        menuItems[selectedMenuItem - 1].setFillColor(menuTextColor);
        menuItems[selectedMenuItem].setFillColor(selectedTextColor);
    }
    else {
        menuItems[maxMenuItems - 1].setFillColor(menuTextColor);
        selectedMenuItem = 0;
        menuItems[selectedMenuItem].setFillColor(selectedTextColor);
    }
}

void ControlMenu::draw()
{
    for (int i = 0; i < maxMenuItems; i++) window.draw(menuItems[i]);
}

void ControlMenu::setMenuTextColors(sf::Color menuColor, sf::Color selectedColor, sf::Color borderColor)
{
    menuTextColor = menuColor;
    selectedTextColor = selectedColor;
    this->borderColor = borderColor;
    for (int i = 0; i < maxMenuItems; i++) {
        menuItems[i].setFillColor(menuTextColor);
        menuItems[i].setOutlineColor(this->borderColor);
    }
    menuItems[selectedMenuItem].setFillColor(selectedTextColor);
}

int ControlMenu::getSelectedIndex() const
{
    return selectedMenuItem;
}
