#include "BossEnemy.h"
#include <cmath>
BossEnemy::BossEnemy(float startX, float startY) : Enemy(startX, startY, 800, 25.0f, 50), regenTimer(0.0f), regenInterval(2.0f)
{
    if (!texture.loadFromFile("Characters/Enemies/boss_enemy.png"))
    {
        sf::Image img;
        img.create(48, 48, sf::Color(255, 200, 0));
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.09f, 0.11f);
    sprite.setOrigin(0, 0);
}
BossEnemy::~BossEnemy() 
{}
void BossEnemy::move(float dt)
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
void BossEnemy::update(float dt) 
{
    updateSlowEffect(dt);
    move(dt);
    regenTimer += dt;
    if (regenTimer >= regenInterval)        //recovering 10 hp after every 2 seconds until it reaches maximum hp
    {
        regenTimer = 0.0f;
        if (hp < max_hp && hp > 0)
        {
            hp += 10;
            if (hp > max_hp)
            {
                hp = max_hp;
            }
        }
    }
}
void BossEnemy::render(sf::RenderWindow& window) 
{
    sprite.setPosition(x - 24, y - 24);
    window.draw(sprite);

    float ratio = (float)hp / (float)max_hp;
    sf::RectangleShape hpBg(sf::Vector2f(40, 7));
    hpBg.setPosition(x - 20, y - 32);
    hpBg.setFillColor(sf::Color(100, 0, 0));
    window.draw(hpBg);
    sf::RectangleShape hpFill(sf::Vector2f(40 * ratio, 7));
    hpFill.setPosition(x - 20, y - 32);
    hpFill.setFillColor(sf::Color(255, 80, 0));
    window.draw(hpFill);
}