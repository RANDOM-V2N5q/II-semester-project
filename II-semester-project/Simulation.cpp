#include "MainHeader.h"



Simulation::Simulation() {
	int windowWidth = 1000;
	int windowHeight = 1000;
	std::string windowName = "Gravity Simulator";
	int windowStyle = sf::Style::Close | sf::Style::Titlebar;
	int windowFramerate = 60;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName, windowStyle);
	window->setFramerateLimit(windowFramerate);

	Radious = 6e+6;
	Mass = 6e+24;
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
		if(event.type == sf::Event::MouseWheelScrolled) {
			double delta = event.mouseWheelScroll.delta;
			sf::View newView = window->getView();
			if(delta > 0) {
				newView.zoom(0.75);
				window->setView(newView);
			}
			else {
				newView.zoom(1.25);
				window->setView(newView);
			}
		}
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::A) {
				sf::View newView = window->getView();
				newView.setCenter(newView.getCenter().x-newView.getSize().x*0.05, newView.getCenter().y);
				window->setView(newView);
			}
			else if(event.key.code == sf::Keyboard::D) {
				sf::View newView = window->getView();
				newView.setCenter(newView.getCenter().x + newView.getSize().x*0.05, newView.getCenter().y);
				window->setView(newView);
			}
			else if(event.key.code == sf::Keyboard::W) {
				sf::View newView = window->getView();
				newView.setCenter(newView.getCenter().x, newView.getCenter().y - newView.getSize().x*0.05);
				window->setView(newView);
			}
			else if(event.key.code == sf::Keyboard::S) {
				sf::View newView = window->getView();
				newView.setCenter(newView.getCenter().x, newView.getCenter().y + newView.getSize().x*0.05);
				window->setView(newView);
			}
			else if(event.key.code == sf::Keyboard::Space) {
				isPaused = !isPaused;
			}
		}
		if(event.type == sf::Event::MouseButtonPressed) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				positonOfMouseL = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			}
			if(event.mouseButton.button == sf::Mouse::Right) {
				positonOfMouseR = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
				isRightMouseButtonPresed = 1;
			}
		}
		if(event.type == sf::Event::MouseButtonReleased) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f newVector = window->mapPixelToCoords(sf::Mouse::getPosition(*window)) - positonOfMouseL;

				sf::CircleShape newShape;
				newShape.setFillColor(sf::Color::White);
				newShape.setOrigin(Radious / 2, Radious / 2);
				newShape.setPosition(positonOfMouseL.x, positonOfMouseL.y);
				newShape.setRadius(Radious);

				CircleObject newObject(Vector2D(newVector.x, newVector.y), Mass, newShape);
				DrawableObjects.push_back(newObject);
			}
			if(event.mouseButton.button == sf::Mouse::Right) {
				isRightMouseButtonPresed = 0;
			}
		}
		if(event.type == sf::Event::MouseMoved && isRightMouseButtonPresed) {
			sf::View newView = window->getView();
			newView.setCenter(newView.getCenter() - (window->mapPixelToCoords(sf::Mouse::getPosition(*window)) - positonOfMouseR));
			window->setView(newView);

			positonOfMouseR = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
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
		if(DrawableObjects[i].getForce().getMagnitude()) {
			Vector2D unitVector = DrawableObjects[i].getForce() / DrawableObjects[i].getForce().getMagnitude();
			Vector2D acceleration = unitVector * DrawableObjects[i].getForce().getMagnitude() / DrawableObjects[i].getMass();

			DrawableObjects[i].setAcceleration(acceleration);
		}
	}
}

void Simulation::calculateVelocitys() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D acceleration = DrawableObjects[i].getAcceleration();
		Vector2D velocity = DrawableObjects[i].getVelocity();

		DrawableObjects[i].setVelocity(velocity + acceleration * 1 / 60);
	}
}

void Simulation::moveObjects() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		Vector2D velocity = DrawableObjects[i].getVelocity();

		Vector2D traveledDistance = (velocity * 1 / 60);
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
		if(!isPaused) {
			update();
		}
		display();
	}
}