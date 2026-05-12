#include "BasicEnemy.h"
#include <cmath>
BasicEnemy::BasicEnemy(float startX, float startY) : Enemy(startX, startY, 100, 60.0f, 10)
{
    if (!texture.loadFromFile("Characters/Enemies/basic_enemy.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(200, 50, 50));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setOrigin(0, 0);
}
BasicEnemy::~BasicEnemy() 
{}
void BasicEnemy::move(float dt)
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
void BasicEnemy::update(float time)
{
    updateSlowEffect(time);
    move(time);
}
void BasicEnemy::render(sf::RenderWindow& window)
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);

    sf::RectangleShape hp_background(sf::Vector2f(40, 5));
    hp_background.setPosition(x - 20, y - 30);
    hp_background.setFillColor(sf::Color(100, 0, 0));
    window.draw(hp_background);

    float ratio = (float)hp / (float)max_hp;
    sf::RectangleShape hpFill(sf::Vector2f(40 * ratio, 5));
    hpFill.setPosition(x - 20, y - 30);
    hpFill.setFillColor(sf::Color::Transparent);
    window.draw(hpFill);
}