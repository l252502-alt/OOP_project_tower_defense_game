#include "FlyingEnemy.h"
#include <cmath>
FlyingEnemy::FlyingEnemy(float startX, float startY, float exitX, float exitY)
    : Enemy(startX, startY, 60, 80.0f, 20),
    exitX(exitX), exitY(exitY) 
{
    setTarget(exitX, exitY);
    if (!texture.loadFromFile("Characters/Enemies/flying_enemy.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(255, 200, 0));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.09f, 0.13f);
    sprite.setOrigin(0, 0);
}
FlyingEnemy::~FlyingEnemy()
{}
void FlyingEnemy::move(float dt)
{
    float dx = exitX - x;
    float dy = exitY - y;
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist < 4.0f)
    {
        reachedEnd = true;
        alive = false;
        return;
    }
    x += (dx / dist) * speed * dt;
    y += (dy / dist) * speed * dt;
}
void FlyingEnemy::update(float dt)
{
    updateSlowEffect(dt);
    move(dt);
}
void FlyingEnemy::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);

    float ratio = (float)hp / (float)max_hp;
    sf::RectangleShape hpBg(sf::Vector2f(30, 5));
    hpBg.setPosition(x - 14, y - 24);
    hpBg.setFillColor(sf::Color(100, 0, 0));
    window.draw(hpBg);
    sf::RectangleShape hpFill(sf::Vector2f(28 * ratio, 5));
    hpFill.setPosition(x - 14, y - 24);
    hpFill.setFillColor(sf::Color(0, 220, 0));
    window.draw(hpFill);
}