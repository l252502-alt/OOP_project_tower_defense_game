#include "MachinegunTower.h"
MachineGunTower::MachineGunTower(float x, float y, int row, int col) : Tower(x, y, row, col, 100.0f, 5.0f, 12, 125, 999)
{
    if (!texture.loadFromFile("Characters/Towers/machinegunTower.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.14f, 0.09f); 
    sprite.setOrigin(0, 0);
}
MachineGunTower::~MachineGunTower() 
{}
void MachineGunTower::attack(Enemy** enemies, int count, float dt)
{
    fireCooldown = fireCooldown - dt;
    if (fireCooldown <= 0.0f)
    {
        Enemy* target = findTarget(enemies, count);
        if (target && bulletCount < max_bullets)
        {
            bullets[bulletCount] = new Bullet(x, y, target, 350.0f, damage, sf::Color(255, 255, 0), 3.0f);
            bulletCount++;
            fireCooldown = 1.0f / fireRate;
        }
    }
}
void MachineGunTower::update(float dt)
{}
void MachineGunTower::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);
}