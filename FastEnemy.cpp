#include "FastEnemy.h"
#include <cmath>
FastEnemy::FastEnemy(float startX, float startY) : Enemy(startX, startY, 40, 100.0f, 15)
{
    if (!texture.loadFromFile("Characters/Enemies/fast_enemy.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(255, 200, 0));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.08f, 0.11f);
    sprite.setOrigin(0, 0);
}
FastEnemy::~FastEnemy() {}
void FastEnemy::move(float dt)
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
void FastEnemy::update(float dt)
{
    updateSlowEffect(dt);
    move(dt);
}
void FastEnemy::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);

    float ratio = (float)hp / (float)max_hp;
    sf::RectangleShape hp_background(sf::Vector2f(40, 5));
    hp_background.setPosition(x - 20, y - 30);
    hp_background.setFillColor(sf::Color(100, 0, 0));
    window.draw(hp_background);
    sf::RectangleShape hpFill(sf::Vector2f(28 * ratio, 5));
    hpFill.setPosition(x - 20, y - 30);
    hpFill.setFillColor(sf::Color(0, 220, 0));
    window.draw(hpFill);
}