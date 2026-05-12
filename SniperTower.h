#pragma once
#ifndef SNIPERTOWER_H
#define SNIPERTOWER_H
#include "Tower.h"
class SniperTower : public Tower
{
public:
    SniperTower(float x, float y, int row, int col);
    ~SniperTower();
    void attack(Enemy** enemies, int count, float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    static int getCostStatic() 
    {
        return 200;
    }
};
#endif