#pragma once
#ifndef BASICENEMY_H
#define BASICENEMY_H
#include "Enemy.h"
class BasicEnemy : public Enemy
{
public:
    BasicEnemy(float startX, float startY);
    ~BasicEnemy();
    void move(float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};
#endif