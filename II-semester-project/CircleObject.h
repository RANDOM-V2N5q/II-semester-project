#pragma once
#include "MainHeader.h"

class CircleObject {
private:
	Vector2D velocity;
	double mass;
	sf::CircleShape object;
public:
	CircleObject();
	CircleObject(Vector2D v, double m, sf::CircleShape o);
	~CircleObject();

	void setVelocity(Vector2D v);
	Vector2D getVelocity();

	void setMass(double m);
	double getMass();

	void setObject(sf::CircleShape o);
	sf::CircleShape getObject();

	Vector2D getPosition();
};
