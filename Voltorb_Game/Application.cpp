
#include "pch.h"

#include "Application.h"
#include "Camera.h"
#include "Game.h"



Application::Application() :
	window_(nullptr),
	camera_(nullptr),
	simulation_(nullptr),
	game_(nullptr),
	keyPressed_(false),
	createdBody_(false)
{
}


Application::~Application()
{
}



bool Application::Init() {


	// initialise stuff
	window_ = new sf::RenderWindow(sf::VideoMode(1020, 720), "SFML works!");
	
	window_->setVerticalSyncEnabled(true);

	window_->setActive(true);

	renderer_.Init(window_);

	camera_ = new Camera();
	camera_->Init(window_);

	game_ = new Game();
	game_->Init();

	// start threads
	// physics thread


	// create stuff for simulation
	//shape_ = new sf::CircleShape(100.0f);
	//shape_->setFillColor(sf::Color::Green);
	keyPressed_ = false;

	running_ = true;
	return true;
}


void Application::CleanUp() {


	renderer_.CleanUp();

	if (window_) {

		window_->close();
		delete window_;
		window_ = nullptr;
	}

	if (camera_) {

		camera_->CleanUp();
		delete camera_;
		camera_ = nullptr;
	}


	//if (shape_) {

	//	delete shape_;
	//	shape_ = nullptr;
	//}

}


bool Application::Update(sf::Time frameTime) {

	if (!window_) {
		
		return false;
	}

	if (!window_->isOpen()) {

		return false;
	}

	if (!CheckEvents(frameTime)) {

		return false;
	}
	if (!CheckInputs(frameTime)) {

		return false;
	}

	camera_->Update(0.01666666667f);


	return true;
}




bool Application::CheckEvents(sf::Time dt) {

	sf::Event event;
	while (window_->pollEvent(event)) {

		if (event.type == sf::Event::Closed) {

			window_->close();
			running_ = false;
			return false;
		}
		else if (event.type == sf::Event::Resized) {

			//window_->setSize(sf::Vector2u(event.size.width, event.size.height));
			sf::View newView = window_->getView();
			newView.setSize((float)event.size.width, (float)event.size.height);
			window_->setView(newView);

			//glViewport(0, 0, event.size.width, event.size.height);
		}

		camera_->OnEvent(event);
		game_->OnEvent(event);
	}

	//shape_->setPosition(shape_->getPosition() + sf::Vector2f(10.0f * dt, 10.0f * dt));

	return true;
}

bool Application::CheckInputs(sf::Time dt) {



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

		running_ = false;
		return false;
	}

	return true;
}


bool Application::Render() {


	renderer_.StartRender();

	//window_->setActive(true);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);

	//glPushMatrix();
		
	//window_->draw(*shape_);
	//window_->display();

	//window_->setActive(false);

	game_->Draw(renderer_);


	renderer_.EndRender();

	return true;
}
