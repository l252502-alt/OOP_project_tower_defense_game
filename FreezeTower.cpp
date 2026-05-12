#include "FreezeTower.h"
FreezeTower::FreezeTower(float x, float y, int row, int col)
    : Tower(x, y, row, col, 130.0f, 0.6f, 20, 175, 999)
{
    if (!texture.loadFromFile("Characters/Towers/freezeTower.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.11f, 0.11f);
    sprite.setOrigin(0, 0);
}
FreezeTower::~FreezeTower()
{}
void FreezeTower::attack(Enemy** enemies, int count, float dt) 
{
    fireCooldown = fireCooldown - dt;
    if (fireCooldown <= 0.0f) 
    {
        Enemy* target = findTarget(enemies, count);
        if (target && bulletCount < max_bullets) 
        {
            bullets[bulletCount] = new Bullet(x, y, target, 180.0f, damage, sf::Color(150, 220, 255), 6.0f, 0.01f, 1.2f);
            bulletCount++;
            fireCooldown = 1.0f / fireRate;
        }
    }
}
void FreezeTower::update(float dt)
{}
void FreezeTower::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 28, y - 28);
    window.draw(sprite);
}