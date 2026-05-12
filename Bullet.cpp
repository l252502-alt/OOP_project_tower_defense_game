#include "Bullet.h"
#include "Enemy.h"
#include <cmath>
Bullet::Bullet(float startX, float startY, Enemy* target, float speed, int damage, sf::Color color, float size,
    float slowFactor, float slowDuration) : x(startX), y(startY), target(target), speed(speed), damage(damage), active(true),
    slowFactor(slowFactor), slowDuration(slowDuration), usesSprite(false) 
{
    if (!texture.loadFromFile("Characters/Bullets/bullet.png"))
    {
        // Fallback: colored circle image
        sf::Image img;
        img.create((int)size * 2, (int)size * 2, color);
        texture.loadFromImage(img);
    }
    sprite.setTexture(texture);
    sprite.setScale(0.06f, 0.06f);
    sprite.setOrigin(size, size);
    usesSprite = true;
}
Bullet::~Bullet() 
{}
bool Bullet::isActive() const
{
    return active;
}
Enemy* Bullet::getTarget() const 
{
    return target; 
}
void Bullet::update(float dt)
{
    if (!active)
    {
        return;
    }
    if (!target || !target->is_alive())
    {
        active = false;
        return;
    }
    float tx = target->getX();
    float ty = target->getY();
    float dx = tx - x;
    float dy = ty - y;
    float dist = std::sqrt(dx * dx + dy * dy);
    if (dist < speed * dt + 4.0f)
    {
        target->takeDamage(damage);
        if (slowFactor < 1.0f)
        {
            target->applySlow(slowFactor, slowDuration);
        }
        active = false;
        return;
    }
    x += (dx / dist) * speed * dt;
    y += (dy / dist) * speed * dt;
}
void Bullet::render(sf::RenderWindow& window)
{
    if (!active)
    {
        return;
    }
    sprite.setPosition(x, y);
    window.draw(sprite);
}