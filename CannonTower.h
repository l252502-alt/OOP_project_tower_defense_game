#pragma once
#ifndef CANNONTOWER_H
#define CANNONTOWER_H
#include "Tower.h"
class CannonTower : public Tower
{
public:
    CannonTower(float x, float y, int row, int col);
    ~CannonTower();
    void attack(Enemy** enemies, int count, float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    static int getCostStatic() 
    {
        return 150; 
    }
};
#endif