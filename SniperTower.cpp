#include "SniperTower.h"
SniperTower::SniperTower(float x, float y, int row, int col) : Tower(x, y, row, col, 280.0f, 0.5f, 100, 200, 999) 
{
    if (!texture.loadFromFile("Characters/Towers/sniperTower.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.13f, 0.13f);
    sprite.setOrigin(0, 0);
}
SniperTower::~SniperTower()
{}
void SniperTower::attack(Enemy** enemies, int count, float dt)
{
    fireCooldown = fireCooldown - dt;
    if (fireCooldown <= 0.0f)
    {
        Enemy* target = findTarget(enemies, count);
        if (target && bulletCount < max_bullets) 
        {
            bullets[bulletCount] = new Bullet(x, y, target, 400.0f, damage, sf::Color(0, 255, 200), 4.0f);
            bulletCount++;
            fireCooldown = 1.0f / fireRate;
        }
    }
}
void SniperTower::update(float dt) 
{}
void SniperTower::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);
}