#include "TankEnemy.h"
#include <cmath>
TankEnemy::TankEnemy(float startX, float startY) : Enemy(startX, startY, 400, 30.0f, 30)
{
    if (!texture.loadFromFile("Characters/Enemies/tank_enemy.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(255, 200, 0));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.23f, 0.19f);
    sprite.setOrigin(0, 0);
}
TankEnemy::~TankEnemy()
{}
void TankEnemy::move(float dt) 
{
    float dx = targetX - x;
    float dy = targetY - y;
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist < 2.0f) 
    {
        x = targetX;
        y = targetY; 
        return; 
    }
    x += (dx / dist) * speed * dt;
    y += (dy / dist) * speed * dt;
}
void TankEnemy::update(float dt)
{
    updateSlowEffect(dt);
    move(dt);
}
void TankEnemy::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);
      
    float ratio = (float)hp / (float)max_hp;
    sf::RectangleShape hpBg(sf::Vector2f(36, 6));
    hpBg.setPosition(x - 18, y - 28);
    hpBg.setFillColor(sf::Color(100, 0, 0));
    window.draw(hpBg);
    sf::RectangleShape hpFill(sf::Vector2f(36 * ratio, 6));
    hpFill.setPosition(x - 18, y - 28);
    hpFill.setFillColor(sf::Color(0, 220, 0));
    window.draw(hpFill);
}