#pragma once
#include "MainHeader.h"

class Simulation {
private:
	const double G = 6.67408e-11;
	sf::RenderWindow *window;
	std::vector<CircleObject> DrawableObjects;
public:
	Simulation();
	~Simulation();

	void event();

	void calculateForces();
	void calculateAcceleration();
	void calculateVelocitys();
	void moveObjects();
	void update();

	void draw();
	void display();

	void run();
};