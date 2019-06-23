#include "MainHeader.h"



void Simulation::changeViewSize(double delta) {
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

void Simulation::changeViewCenter() {
	sf::View newView = window->getView();
	newView.setCenter(newView.getCenter() - (getCursorPosition() - positonOfRightMouseClick));
	window->setView(newView);

	savePositionOfCursorTo(&positonOfRightMouseClick);
}

sf::Vector2f Simulation::getCursorPosition() {
	return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Simulation::savePositionOfCursorTo(sf::Vector2f * var) {
	*var = getCursorPosition();
}

void Simulation::createObject() {
	sf::Vector2f velocity = getCursorPosition() - positonOfLeftMouseClick;

	sf::CircleShape shape;
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(Radious, Radious);
	shape.setPosition(positonOfLeftMouseClick);
	shape.setRadius(Radious);

	CircleObject newObject(velocity, Mass, shape);
	DrawableObjects.push_back(newObject);
}

void Simulation::deleteObject(int i) {
	DrawableObjects.erase(DrawableObjects.begin() + i);
}



Simulation::Simulation() {
	int windowWidth = 1000;
	int windowHeight = 1000;
	std::string windowName = "Gravity Simulator";
	int windowStyle = sf::Style::Close | sf::Style::Titlebar;
	sf::ContextSettings windowSetting;
	windowSetting.antialiasingLevel = 4;
	int windowFramerate = 60;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowName, windowStyle, windowSetting);
	window->setFramerateLimit(windowFramerate);
	window->setView(sf::View(sf::FloatRect(0, 0, 7e+8, 7e+8)));

	Radious = 6e+6;
	Mass = 6e+24;
	speedOfSimulation = 1;
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
		else if(event.type == sf::Event::MouseWheelScrolled) {
			changeViewSize(event.mouseWheelScroll.delta);
		}
		else if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Space) {
				isPaused = !isPaused;
			}
			else if(event.key.code == sf::Keyboard::Comma) {
				if(speedOfSimulation > 0) {
					speedOfSimulation--;
				}
			}
			else if(event.key.code == sf::Keyboard::Period) {
				speedOfSimulation++;
			}
		}
		else if(event.type == sf::Event::MouseButtonPressed) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				savePositionOfCursorTo(&positonOfLeftMouseClick);
			}
			else if(event.mouseButton.button == sf::Mouse::Right) {
				savePositionOfCursorTo(&positonOfRightMouseClick);
				isRightMouseButtonPressed = 1;
			}
		}
		else if(event.type == sf::Event::MouseButtonReleased) {
			if(event.mouseButton.button == sf::Mouse::Left) {
				createObject();
			}
			else if(event.mouseButton.button == sf::Mouse::Right) {
				isRightMouseButtonPressed = 0;
			}
		}
		else if(event.type == sf::Event::MouseMoved && isRightMouseButtonPressed) {
			changeViewCenter();
		}
	}
}



bool Simulation::isCollision(CircleObject a, CircleObject b) {
	Vector2D pos1 = a.getPosition();
	double radious = a.getObject().getRadius();
	Vector2D pos2 = b.getPosition();

	return pow(pos2.getX() - pos1.getX(), 2) + pow(pos2.getY() - pos1.getY(), 2) <= pow(radious, 2);
}

void Simulation::mergeObjects(int i, int j) {
	double m1 = DrawableObjects[i].getMass();
	Vector2D v1 = DrawableObjects[i].getVelocity();
	double m2 = DrawableObjects[j].getMass();
	Vector2D v2 = DrawableObjects[j].getVelocity();

	DrawableObjects[i].setVelocity((v1*m1 + v2 * m2) / (m1 + m2));
	DrawableObjects[i].setMass(m1 + m2);
}

void Simulation::detectCollisions() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		for(int j = i + 1; j < DrawableObjects.size(); j++) {
			if(isCollision(DrawableObjects[i], DrawableObjects[j])) {
				mergeObjects(i, j);
				deleteObject(j);
				j--;
			}
		}
	}
}

void Simulation::resetForces() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		DrawableObjects[i].setForce(Vector2D(0, 0));
	}
}

void Simulation::calculateForces() {
	resetForces();

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

void Simulation::calculateAccelerations() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		if(DrawableObjects[i].getForce().getMagnitude()) {
			Vector2D unitVector = DrawableObjects[i].getForce() / DrawableObjects[i].getForce().getMagnitude();
			Vector2D acceleration = unitVector * DrawableObjects[i].getForce().getMagnitude() / DrawableObjects[i].getMass();

			DrawableObjects[i].setAcceleration(acceleration);
		}
		else {
			DrawableObjects[i].setAcceleration(Vector2D(0, 0));
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

		lines.push_back(sf::Vertex(sf::Vector2f(position.getX() + traveledDistance.getX(),position.getY() + traveledDistance.getY())));
		lines.push_back(sf::Vertex(sf::Vector2f(position.getX(), position.getY())));

		DrawableObjects[i].setPosition(position + traveledDistance);
	}
}

void Simulation::update() {
	detectCollisions();
	calculateForces();
	calculateAccelerations();
	calculateVelocitys();
	moveObjects();
}



void Simulation::draw() {
	for(int i = 0; i < DrawableObjects.size(); i++) {
		window->draw(DrawableObjects[i].getObject());
	}
	if(lines.size() != 0) {
		window->draw(&lines[0], lines.size(), sf::Lines);
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
		for(int i = 0; (i < speedOfSimulation) && (isPaused == false); i++) {
			update();
		}
		display();
	}
}