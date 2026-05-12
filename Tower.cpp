#include "Tower.h"
#include <cmath>
Tower::Tower(float x, float y, int row, int col, float range, float fireRate, int damage, int cost, int hp)
    : Entity(x, y, hp), range(range), fireRate(fireRate), fireCooldown(0.0f),
    damage(damage), cost(cost), row(row), col(col), bulletCount(0)
{
    for (int i = 0; i < max_bullets; i++)
        bullets[i] = nullptr;
}
Tower::~Tower()
{
    for (int i = 0; i < max_bullets; i++)
    {
        delete bullets[i];
        bullets[i] = nullptr;
    }
}
int Tower::getCost() const 
{
    return cost; 
}
int Tower::getRow() const 
{
    return row;
}
int Tower::getCol() const 
{
    return col;
}
float Tower::getRange() const 
{
    return range; 
}
Enemy* Tower::findTarget(Enemy** enemies, int count) 
{
    // Target the enemy that has progressed furthest along the path
    Enemy* best = nullptr;
    int bestWP = -1;
    for (int i = 0; i < count; i++)
    {
        if (!enemies[i] || !enemies[i]->is_alive())
            continue;
        float dx = enemies[i]->getX() - x;
        float dy = enemies[i]->getY() - y;
        float dist = std::sqrt(dx * dx + dy * dy);
        if (dist <= range) 
        {
            if (enemies[i]->getWaypointIndex() > bestWP)
            {
                bestWP = enemies[i]->getWaypointIndex();
                best = enemies[i];
            }
        }
    }
    return best;
}
void Tower::updateBullets(float dt)
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (bullets[i])
        {
            bullets[i]->update(dt);
            if (!bullets[i]->isActive()) 
            {
                delete bullets[i];
                bullets[i] = nullptr;
                // Shift array left
                for (int j = i; j < bulletCount - 1; j++)
                {
                    bullets[j] = bullets[j + 1];
                }
                bullets[bulletCount - 1] = nullptr;
                bulletCount--;
                i--;
            }
        }
    }
}
void Tower::renderBullets(sf::RenderWindow& window)
{
    for (int i = 0; i < bulletCount; i++)
    {
        if (bullets[i]) bullets[i]->render(window);
    }
}
void Tower::renderRange(sf::RenderWindow& window, bool selected) 
{
    if (!selected)
        return;
    sf::CircleShape rangeCircle(range);
    rangeCircle.setPosition(x - range, y - range);
    rangeCircle.setFillColor(sf::Color(255, 255, 255, 30));
    rangeCircle.setOutlineColor(sf::Color(255, 255, 255, 100));
    rangeCircle.setOutlineThickness(1);
    window.draw(rangeCircle);
}