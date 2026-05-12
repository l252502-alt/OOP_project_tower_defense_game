#pragma once
#ifndef MACHINEGUNTOWER_H
#define MACHINEGUNTOWER_H
#include "Tower.h"
class MachineGunTower : public Tower
{
public:
    MachineGunTower(float x, float y, int row, int col);
    ~MachineGunTower();
    void attack(Enemy** enemies, int count, float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    static int getCostStatic() 
    {
        return 125;
    }
};
#endif