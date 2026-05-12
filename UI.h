#pragma once
#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
class UI
{
private:
    sf::Font font;
    bool fontLoaded;
    int gold;
    int lives;
    int waveNumber;
    int totalWaves;
    int selectedTower; 
public:
    UI();
    ~UI();
    bool loadFont(const std::string& fontPath);
    void setGold(int g);
    void setLives(int l);
    void setWave(int w, int total);
    void setSelectedTower(int t);
    int getGold() const;
    int getLives() const;
    int getSelectedTower() const;
    int getSelectedTowerCost() const;
    void render(sf::RenderWindow& window);
    void renderTowerMenu(sf::RenderWindow& window);
};
#endif