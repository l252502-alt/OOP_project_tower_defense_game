#pragma once
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
class Enemy;                  //declared because its pointers used in this class
class Bullet
{
private:
    float x, y;
    float speed;
    int damage;
    bool active;
    Enemy* target;
    float slowFactor;        //decides how slow the bullet will make the enemy thrown by slow tower
    float slowDuration;
    sf::Texture texture;
    sf::Sprite sprite;
    bool usesSprite;
public:
    Bullet(float startX, float startY, Enemy* target, float speed, int damage, sf::Color color, float size = 5.0f, float slowFactor = 1.0f, float slowDuration = 0.0f);
    ~Bullet();
    bool isActive() const;
    Enemy* getTarget() const;
    void update(float dt);
    void render(sf::RenderWindow& window);
};
#endif