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

		//https://i.stack.imgur.com/owYYV.png

			Vector2D unitVector = (position2 - position1) / (position2 - position1).getMagnitude();
			Vector2D gForce = unitVector * G*mass1*mass2 / (position2 - position1).getMagnitude();

			DrawableObjects[i].setForce(gForce + DrawableObjects[i].getForce());
			DrawableObjects[j].setForce(-gForce + DrawableObjects[j].getForce());
		}
	}
}

void Simulation::calculateAcceleration() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D unitVector = DrawableObjects[i].getForce() / DrawableObjects[i].getForce().getMagnitude();
		Vector2D acceleration = unitVector * DrawableObjects[i].getForce().getMagnitude() / DrawableObjects[i].getMass();

		DrawableObjects[i].setAcceleration(acceleration);
	}
}

void Simulation::calculateVelocitys() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D acceleration = DrawableObjects[i].getAcceleration();
		Vector2D velocity = DrawableObjects[i].getVelocity();

		DrawableObjects[i].setVelocity(velocity + acceleration * 1000 / 60);
	}
}

void Simulation::moveObjects() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D velocity = DrawableObjects[i].getVelocity();

		Vector2D traveledDistance = (velocity * 1000 / 60);
		Vector2D position = DrawableObjects[i].getPosition();

		DrawableObjects[i].setPosition(position + traveledDistance);
	}
}

void Simulation::update() {
	calculateForces();
	calculateAcceleration();
	calculateVelocitys();
	moveObjects();
}



void Simulation::draw() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		window->draw(DrawableObjects[i].getObject());
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