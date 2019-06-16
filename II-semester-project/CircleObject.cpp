#include "MainHeader.h"



CircleObject::CircleObject() {
	force = Vector2D();
	object = sf::CircleShape();
}

CircleObject::CircleObject(Vector2D v, double m, sf::CircleShape o) {
	force = v;
	mass = m;
	object = o;
}

CircleObject::~CircleObject() {
}



void CircleObject::setForce(Vector2D v) {
	force = v;
}

Vector2D CircleObject::getForce() {
	return force;
}



void CircleObject::setAcceleration(Vector2D v) {
	acceleration = v;
}

Vector2D CircleObject::getAcceleration() {
	return acceleration;
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

void CircleObject::setPosition(double x, double y) {
	object.setPosition(x, y);
}

void CircleObject::setPosition(Vector2D v) {
	object.setPosition(v.getX(), v.getY());
}
