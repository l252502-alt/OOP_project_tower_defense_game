#pragma once
#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H
#include "Enemy.h"
class FlyingEnemy : public Enemy 
{
private:
    float exitX, exitY;
public:
    FlyingEnemy(float startX, float startY, float exitX, float exitY);
    ~FlyingEnemy();
    void move(float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};
#endif