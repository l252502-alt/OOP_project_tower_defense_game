#include "UI.h"
#include "CannonTower.h"
#include "SniperTower.h"
#include "MachineGunTower.h"
#include "SlowTower.h"
#include "FreezeTower.h"
#include <string>
UI::UI() : gold(200), lives(10), waveNumber(1),
totalWaves(5), selectedTower(-1), fontLoaded(false)
{
}
UI::~UI() 
{}
bool UI::loadFont(const std::string& fontPath)
{
    fontLoaded = font.loadFromFile(fontPath);
    return fontLoaded;
}
void UI::setGold(int g) 
{
    gold = g; 
}
void UI::setLives(int l) 
{
    lives = l;
}
void UI::setWave(int w, int total) 
{
    waveNumber = w; 
    totalWaves = total;
}
void UI::setSelectedTower(int t) 
{
    selectedTower = t; 
}
int UI::getGold() const 
{
    return gold;
}
int UI::getLives() const 
{
    return lives; 
}
int UI::getSelectedTower() const 
{
    return selectedTower; 
}
int UI::getSelectedTowerCost() const 
{
    switch (selectedTower) 
    {
    case 0:
        return CannonTower::getCostStatic();
    case 1:
        return SniperTower::getCostStatic();
    case 2:
        return MachineGunTower::getCostStatic();
    case 3:
        return SlowTower::getCostStatic();
    case 4:
        return FreezeTower::getCostStatic();
    default:
        return 0;
    }
}
void UI::render(sf::RenderWindow& window)
{
    if (!fontLoaded)
    {
        return;
    }
    sf::RectangleShape bar(sf::Vector2f(960, 36));
    bar.setPosition(0, 720);
    bar.setFillColor(sf::Color(30, 30, 30));
    window.draw(bar);

    sf::Text goldText, livesText, waveText;
    goldText.setFont(font); livesText.setFont(font); waveText.setFont(font);
    goldText.setCharacterSize(20); livesText.setCharacterSize(20); waveText.setCharacterSize(20);
    goldText.setFillColor(sf::Color::Yellow);
    livesText.setFillColor(sf::Color::Red);
    waveText.setFillColor(sf::Color::White);

    goldText.setString("Gold: " + std::to_string(gold));
    livesText.setString("Lives: " + std::to_string(lives));
    waveText.setString("Wave: " + std::to_string(waveNumber) + "/" + std::to_string(totalWaves));

    goldText.setPosition(10, 722);
    livesText.setPosition(200, 722);
    waveText.setPosition(400, 722);

    window.draw(goldText);
    window.draw(livesText);
    window.draw(waveText);
}
void UI::renderTowerMenu(sf::RenderWindow& window)
{
    if (!fontLoaded)
    {
        return;
    }
    const char* names[] = { "Cannon\nRs.150", "Sniper\nRs.200", "MachGun\nRs.125", "Slow\nRs.100", "Freeze\nRs.175" };
    for (int i = 0; i < 5; i++)
    {
        sf::RectangleShape btn(sf::Vector2f(80, 60));
        btn.setPosition(580 + i * 76, 700);
        btn.setFillColor(sf::Color::Transparent);
        if (selectedTower == i)
        {
            btn.setOutlineColor(sf::Color::White);
            btn.setOutlineThickness(3);
        }
        else
        {
            btn.setOutlineColor(sf::Color(100, 100, 100));
            btn.setOutlineThickness(1);
        }
        window.draw(btn);

        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(11);
        label.setFillColor(sf::Color::White);
        label.setString(names[i]);
        label.setPosition(585 + i * 76, 704);
        window.draw(label);
    }
}