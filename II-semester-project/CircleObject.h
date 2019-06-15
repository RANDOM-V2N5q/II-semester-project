#pragma once
#include "MainHeader.h"

class CircleObject {
private:
	Vector2D velocity;
	sf::CircleShape object;
public:
	CircleObject();
	CircleObject(Vector2D v, sf::CircleShape o);
	~CircleObject();

	void setVelocity(Vector2D v);
	Vector2D getVelocity();

	void setObject(sf::CircleShape o);
	sf::CircleShape getObject();
};
