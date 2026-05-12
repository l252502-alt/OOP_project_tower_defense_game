#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
class Enemy : public Entity 
{
protected:
    float speed;
    int goldReward;
    bool reachedEnd;
    float slowTime;      
    float originalSpeed;
    int waypointIndex;    //current position on path
    float targetX;        //positions of garget checkpoint
    float targetY;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Enemy(float startX, float startY, int hp, float speed, int goldReward);
    virtual ~Enemy();
    float getSpeed() const;
    int getGoldReward() const;
    bool hasReachedEnd() const;
    int getWaypointIndex() const;
    void applySlow(float newSpeed, float duration);
    void updateSlowEffect(float time);             //restores original speed
    void setTarget(float tx, float ty);
    void advanceWaypoint();
    virtual void takeDamage(int amount);
    virtual void move(float time) = 0;
    virtual void update(float time) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
#endif