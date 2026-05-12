#include "Enemy.h"
#include <cmath>
#include <SFML/Graphics.hpp>
Enemy::Enemy(float startX, float startY, int hp, float speed, int goldReward) : Entity(startX, startY, hp),
    speed(speed), originalSpeed(speed), goldReward(goldReward), reachedEnd(false), slowTime(0.0f), waypointIndex(0),
    targetX(startX), targetY(startY) 
{
}
Enemy::~Enemy() 
{}
float Enemy::getSpeed() const 
{
    return speed; 
}
int Enemy::getGoldReward() const 
{
    return goldReward; 
}
bool Enemy::hasReachedEnd() const
{
    return reachedEnd; 
}
int Enemy::getWaypointIndex() const
{
    return waypointIndex; 
}
void Enemy::applySlow(float newSpeed, float duration)
{
    speed = originalSpeed * newSpeed;
    slowTime = duration;
}
void Enemy::updateSlowEffect(float time)
{
    if (slowTime > 0) 
    {
        slowTime = slowTime - time;
        if (slowTime <= 0)
        {
            slowTime = 0;
            speed = originalSpeed;
        }
    }
}
void Enemy::setTarget(float tx, float ty)
{
    targetX = tx;
    targetY = ty;
}
void Enemy::advanceWaypoint()
{
    waypointIndex++;
}
void Enemy::takeDamage(int amount) 
{
    set_hp(get_hp() - amount);
}