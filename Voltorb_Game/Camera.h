#pragma once
#include "pch.h"


class Camera :
	public sf::View
{
public:
	Camera();
	~Camera();


	void Init(sf::RenderWindow* newWindow);
	void CleanUp();


	void Update(float frameTime);
	void OnEvent(sf::Event& event);


	inline void SetSpeed(float newSpeed) { speed_ = newSpeed; }

protected:

	float speed_;
	float zoomSpeed_;


	float mouseScrollSpeed_;
	bool mouseScrollPressed_;

	sf::Vector2f gotoPos_;
	sf::Vector2f releaseVelocity_;
	sf::Vector2f slowDirection_;
	float releaseSlowFactor_;

	float scaleFactor_;


	sf::RenderWindow* window_;

};

