#include "MainHeader.h"



Simulation::Simulation() {
	int windowWidth = 1000;
	int windowHeight = 1000;
	std::string windowName = "Gravity Simulator";
	int windowStyle = sf::Style::Close | sf::Style::Titlebar;
	int windowFramerate = 60;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName, windowStyle);
	window->setFramerateLimit(windowFramerate);
}

Simulation::~Simulation() {
	delete window;
}



void Simulation::event() {
	sf::Event event;

	while(window->pollEvent(event)) {
		if(event.type == sf::Event::Closed) {
			window->close();
		}
	}
}



void Simulation::calculateForces() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		double mass1 = DrawableObjects[i].getMass();
		Vector2D position1 = DrawableObjects[i].getPosition();

		for(int j = i + 1; j < DrawableObjects.size(); j++) {
			double mass2 = DrawableObjects[j].getMass();
			Vector2D position2 = DrawableObjects[j].getPosition();

		https://i.stack.imgur.com/owYYV.png

			Vector2D distance = position2 - position1;
			Vector2D gForce = (distance*G*mass1*mass2) / pow(hypot(distance.getX(), distance.getY), 3);

			DrawableObjects[i].setVelocity(gForce + DrawableObjects[i].getVelocity());
			DrawableObjects[j].setVelocity(-(gForce + DrawableObjects[j].getVelocity()));
		}
	}
}

void Simulation::moveObjects() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D velocity = DrawableObjects[i].getVelocity();
		double mass = DrawableObjects[i].getMass();

		double traveledDistance = (velocity.getMagnitude()*1000/60)/mass;
		double traveledDistanceX = cos(velocity.getDirection())*traveledDistance;
		double traveledDistanceY = sin(velocity.getDirection())*traveledDistance;

		double positionX = DrawableObjects[i].getPosition().getX();
		double positionY = DrawableObjects[i].getPosition().getY();

		DrawableObjects[i].setPosition(positionX + traveledDistanceX, positionY + traveledDistanceY);
	}
}

void Simulation::update() {
	calculateForces();
	moveObjects();
}



void Simulation::draw() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		window->draw(DrawableObjects[i].getObject);
	}
}

void Simulation::display() {
	window->clear();
	draw();
	window->display();
}



void Simulation::run() {
	while(window->isOpen()) {
		event();
		update();
		display();
	}
}