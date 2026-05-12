#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
class Entity
{
protected:
	float x, y;
	int hp;
	int max_hp;
	bool alive;
public:
	Entity(float a, float b, int h_p);
	virtual ~Entity();
	float getX() const;
	float getY() const;
	int get_hp() const;
	int get_max_hp() const;
	bool is_alive() const;
	void setX(float x);
	void setY(float y);
	void set_hp(int hp);
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	bool operator>(const Entity& other) const;
};
#endif