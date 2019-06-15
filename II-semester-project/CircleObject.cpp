#include "MainHeader.h"



CircleObject::CircleObject() {
	velocity = Vector2D();
	object = sf::CircleShape();
}

CircleObject::CircleObject(Vector2D v, sf::CircleShape o) {
	velocity = v;
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



void  CircleObject::setObject(sf::CircleShape o) {
	object = o;
}

sf::CircleShape  CircleObject::getObject() {
	return object;
}
