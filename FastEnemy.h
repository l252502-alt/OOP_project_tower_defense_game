#pragma once
#ifndef FASTENEMY_H
#define FASTENEMY_H

#include "Enemy.h"

class FastEnemy : public Enemy {
public:
    FastEnemy(float startX, float startY);
    ~FastEnemy();

    void move(float dt) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif