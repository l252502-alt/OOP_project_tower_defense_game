#pragma once
#ifndef BOSSENEMY_H
#define BOSSENEMY_H
#include "Enemy.h"
class BossEnemy : public Enemy          //custom enemy. high hp, restores hp with time
{
private:
    float regenTimer;
    float regenInterval;        //interval after which it recovers
public:
    BossEnemy(float startX, float startY);
    ~BossEnemy();
    void move(float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};
#endif