#include "MainHeader.h"



CircleObject::CircleObject() {
	velocity = Vector2D();
	object = sf::CircleShape();
}

CircleObject::CircleObject(Vector2D v, double m, sf::CircleShape o) {
	velocity = v;
	mass = m;
	object = o;
}

CircleObject::~CircleObject() {
}



void CircleObject::setVelocity(Vector2D v) {
	velocity = v;
}

Vector2D CircleObject::getVelocity() {
	return velocity;
}



void CircleObject::setMass(double m) {
	mass = m;
}

double CircleObject::getMass() {
	return mass;
}



void  CircleObject::setObject(sf::CircleShape o) {
	object = o;
}

sf::CircleShape  CircleObject::getObject() {
	return object;
}

Vector2D CircleObject::getPosition() {
	return Vector2D(object.getPosition().x, object.getPosition().y);
}
