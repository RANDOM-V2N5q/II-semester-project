#pragma once
#include "MainHeader.h"

class Simulation {
private:
	const double G = 6.67408e-11;
	sf::RenderWindow *window;
	std::vector<CircleObject> DrawableObjects;

	sf::Vector2f positonOfLeftMouseClick;
	sf::Vector2f positonOfRightMouseClick;
	bool isRightMouseButtonPressed;
	bool isPaused;
	double radius;
	double mass;


	void changeViewSize(double delta);
	void changeViewCenter();
	sf::Vector2f getCursorPosition();
	void savePositionOfCursorTo(sf::Vector2f *var);
	void createObject();
	void deleteObject(int i);
public:
	Simulation();
	~Simulation();

	void event();

	bool isCollision(CircleObject a, CircleObject b);
	void mergeObjects(int i, int j);
	void detectCollisions();
	void resetForces();
	void calculateForces();
	void calculateAccelerations();
	void calculateVelocitys();
	void moveObjects();
	void update();

	void draw();
	void display();

	void run();
};