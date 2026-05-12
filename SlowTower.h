#pragma once
#ifndef SLOWTOWER_H
#define SLOWTOWER_H
#include "Tower.h"
class SlowTower : public Tower
{
private:
    float pulseTimer;
    float pulseInterval;
public:
    SlowTower(float x, float y, int row, int col);
    ~SlowTower();
    void attack(Enemy** enemies, int count, float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    static int getCostStatic() 
    {
        return 100; 
    }
};
#endif