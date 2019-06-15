#pragma once
#include "MainHeader.h"

class Simulation {
private:
	double static G;
	sf::RenderWindow *window;
	std::vector<CircleObject> DrawableObjects;
public:
	Simulation();
	~Simulation();

	void event();

	void calculateForces();
	void moveObjects();
	void update();

	void draw();
	void display();

	void run();
};

double Simulation::G = 6.67408e-11;