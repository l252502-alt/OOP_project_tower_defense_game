#pragma once
#ifndef TANKENEMY_H
#define TANKENEMY_H
#include "Enemy.h"
class TankEnemy : public Enemy
{
public:
    TankEnemy(float startX, float startY);
    ~TankEnemy();
    void move(float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};
#endif