#pragma once
#ifndef FREEZETOWER_H
#define FREEZETOWER_H
#include "Tower.h"
class FreezeTower : public Tower
{
public:
    FreezeTower(float x, float y, int row, int col);
    ~FreezeTower();
    void attack(Enemy** enemies, int count, float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    static int getCostStatic()
    {
        return 175; 
    }
};
#endif