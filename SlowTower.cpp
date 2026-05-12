#include "SlowTower.h"
#include <cmath>
SlowTower::SlowTower(float x, float y, int row, int col) : Tower(x, y, row, col, 110.0f, 1.0f, 5, 100, 999), pulseTimer(0.0f), pulseInterval(1.5f)
{
    if (!texture.loadFromFile("Characters/Towers/slowTower.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.18f, 0.15f);
    sprite.setOrigin(0, 0);
}
SlowTower::~SlowTower()
{}
void SlowTower::attack(Enemy** enemies, int count, float dt) 
{
    pulseTimer = pulseTimer + dt;
    if (pulseTimer >= pulseInterval)
    {
        pulseTimer = 0.0f;
        for (int i = 0; i < count; i++) 
        {
            if (!enemies[i] || !enemies[i]->is_alive())
            {
                continue;
            }
            float dx = enemies[i]->getX() - x;
            float dy = enemies[i]->getY() - y;
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist <= range)
            {
                enemies[i]->applySlow(0.4f, 2.0f);
                enemies[i]->takeDamage(damage);
            }
        }
    }
}
void SlowTower::update(float dt)
{}
void SlowTower::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);
}