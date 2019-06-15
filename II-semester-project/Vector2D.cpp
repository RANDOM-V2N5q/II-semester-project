#include "MainHeader.h"



Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(double X, double Y) {
	x = X;
	y = Y;
}

Vector2D::~Vector2D() {
}



void Vector2D::setX(double X) {
	x = X;
}

double Vector2D::getX() {
	return x;
}



void Vector2D::setY(double Y) {
	y = Y;
}

double Vector2D::getY() {
	return y;
}



double Vector2D::getMagnitude() {
	return hypot(x, y);
}

double Vector2D::getDirection() {
	return atan(y/x);
}



Vector2D Vector2D::operator+(Vector2D v) {
	return Vector2D(
		x + v.getX(),
		y + v.getY()
	);
}

Vector2D Vector2D::operator-(Vector2D v) {
	return Vector2D(
		x - v.getX(),
		y - v.getY()
	);
}

Vector2D Vector2D::operator*(double a) {
	return Vector2D(x*a, y*a);
}

Vector2D Vector2D::operator/(double a) {
	return Vector2D(x/a, y/a);
}

Vector2D Vector2D::operator-() {
	return Vector2D(-x, -y);
}
