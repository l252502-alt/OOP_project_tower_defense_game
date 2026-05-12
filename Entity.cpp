#include "Entity.h"
Entity::Entity(float a, float b, int h_p) : x(a), y(b), hp(h_p), alive(true)
{
}
Entity::~Entity()
{
}
float Entity::getX() const
{
	return x;
}
float Entity::getY() const
{
	return y;
}
int Entity::get_hp() const
{
	return hp;
}
int Entity::get_max_hp() const
{
	return max_hp;
}
bool Entity::is_alive() const
{
	return alive;
}
void Entity::setX(float x_)
{
	x = x_;
}
void Entity::setY(float y_)
{
	y = y_;
}
void Entity::set_hp(int h)
{
	hp = h;
	if (hp < 0)
	{
		hp = 0;
		alive = false;
	}
}
bool Entity::operator>(const Entity& other) const
{
	return hp > other.hp;
}