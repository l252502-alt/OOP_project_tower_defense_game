#include "CannonTower.h"
CannonTower::CannonTower(float x, float y, int row, int col) : Tower(x, y, row, col, 120.0f, 0.8f, 60, 150, 999) 
{
    if (!texture.loadFromFile("Characters/Towers/canonTower.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.13f, 0.13f);
    sprite.setOrigin(0, 0);
}
CannonTower::~CannonTower()
{}
void CannonTower::attack(Enemy** enemies, int count, float dt)
{
    fireCooldown -= dt;
    if (fireCooldown <= 0.0f)
    {
        Enemy* target = findTarget(enemies, count);
        if (target && bulletCount < max_bullets)
        {
            bullets[bulletCount] = new Bullet(x, y, target, 200.0f, damage, sf::Color(200, 100, 0), 7.0f);
            bulletCount++;
            fireCooldown = 1.0f / fireRate;
        }
    }
}
void CannonTower::update(float dt)
{
}
void CannonTower::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);
}