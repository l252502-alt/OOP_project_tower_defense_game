#pragma once
#ifndef TOWER_H
#define TOWER_H
#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
const int max_bullets = 50;
class Tower : public Entity
{
protected:
    float range;
    float fireRate;                //shots per second
    float fireCooldown;            //current cooldown timer
    int damage;
    int cost;
    int col, row;                   //grid position of tower
    Bullet* bullets[max_bullets];
    int bulletCount;
    sf::Texture texture;
    sf::Sprite sprite;
    Enemy* findTarget(Enemy** enemies, int count);          //finding first enemy in range
public:
    Tower(float x, float y, int row, int col, float range, float fireRate, int damage, int cost, int hp);
    virtual ~Tower();
    int getCost() const;
    int getRow() const;
    int getCol() const;
    float getRange() const;
    void updateBullets(float dt);
    void renderBullets(sf::RenderWindow& window);
    void renderRange(sf::RenderWindow& window, bool selected);
    virtual void attack(Enemy** enemies, int count, float dt) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
#endif