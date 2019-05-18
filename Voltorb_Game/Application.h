#pragma once


//#include <SFML/OpenGL.hpp>
#include "pch.h"

#include "Renderer.h"

class Simulation;
class Camera;
class Game;

class Application
{
public:
	Application();
	~Application();


	bool Init();

	void CleanUp();


	bool Update(sf::Time frameTime);
	bool Render();


	inline bool IsRunning() { return running_; }


protected:

	bool CheckEvents(sf::Time dt);
	bool CheckInputs(sf::Time dt);

	sf::RenderWindow* window_;
	//sf::CircleShape* shape_;

	Renderer renderer_;
	Simulation* simulation_;
	Camera* camera_;

	Game* game_;

	bool keyPressed_;
	bool createdBody_;


	bool running_;
};

