#pragma once
#include "MainHeader.h"

class CircleObject {
private:
	Vector2D force;
	Vector2D acceleration;
	Vector2D velocity;
	double mass;
	sf::CircleShape object;
public:
	CircleObject();
	CircleObject(Vector2D v, double m, sf::CircleShape o);
	~CircleObject();

	void setForce(Vector2D v);
	Vector2D getForce();

	void setAcceleration(Vector2D v);
	Vector2D getAcceleration();

	void setVelocity(Vector2D v);
	Vector2D getVelocity();

	void setMass(double m);
	double getMass();

	void setObject(sf::CircleShape o);
	sf::CircleShape getObject();

	Vector2D getPosition();
	void setPosition(double x, double y);
	void setPosition(Vector2D v);
};
