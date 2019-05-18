
#include "pch.h"

#include "Camera.h"
#include "PhysicsUtil.h"



Camera::Camera() :
	speed_(100.0f),
	zoomSpeed_(0.1f),
	mouseScrollSpeed_(20.0f),
	mouseScrollPressed_(false),
	releaseSlowFactor_(7000.0f),
	scaleFactor_(1.0f)
{
}


Camera::~Camera()
{
}


void Camera::Init(sf::RenderWindow* newWindow) {

	window_ = newWindow;

	setSize(1020.0f, 720.0f);
}

void Camera::CleanUp() {


}


void Camera::Update(float frameTime) {


	sf::Vector2f movement;

	if (mouseScrollPressed_) {

		movement = (sf::Vector2f)window_->mapCoordsToPixel(gotoPos_) - (sf::Vector2f)sf::Mouse::getPosition();

		movement *= mouseScrollSpeed_;

		releaseVelocity_ = movement;
	}
	else {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			movement.x += speed_;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			movement.x -= speed_;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			movement.y -= speed_;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

			movement.y += speed_;
		}

		if (releaseVelocity_.x != 0) {
			if (movement.x == 0.0f && movement.y == 0.0f) {

				

				releaseVelocity_ += slowDirection_ * releaseSlowFactor_ * frameTime;
				movement = releaseVelocity_;

				if (PhysicsUtil::VectorLengthSqr(releaseVelocity_ * frameTime) <= powf((releaseSlowFactor_ * frameTime * frameTime), 2)) {
					releaseVelocity_.x = 0.0f;
					releaseVelocity_.y = 0.0f;
				}
			}
			else {

				releaseVelocity_.x = 0.0f;
				releaseVelocity_.y = 0.0f;
			}
		}
	}

	
	movement *= frameTime * scaleFactor_;
	move(movement);


}


void Camera::OnEvent(sf::Event& event) {


	if (event.type == sf::Event::MouseWheelScrolled) {

		if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

			sf::Vector2f mouseMapPos = window_->mapPixelToCoords(sf::Vector2i(event.mouseWheelScroll.x, event.mouseWheelScroll.y));

			sf::Vector2f mouseToCenter = getCenter() - mouseMapPos;

			float zoomFactor = 1.0f;

			if (event.mouseWheelScroll.delta > 0) {
				zoomFactor -= zoomSpeed_;
			}
			else {
				zoomFactor += zoomSpeed_;
			}

			zoom(zoomFactor);

			scaleFactor_ = getSize().x / 1280.0f;

			mouseToCenter *= zoomFactor;

			setCenter(mouseToCenter + mouseMapPos);

			

		}
	}

	if (!mouseScrollPressed_) {
		if (event.type == sf::Event::MouseButtonPressed) {

			if (event.mouseButton.button == sf::Mouse::Right) {

				mouseScrollPressed_ = true;
				gotoPos_ = window_->mapPixelToCoords(sf::Mouse::getPosition());

			}
		}
	}
	else {

		if (event.type == sf::Event::MouseButtonReleased) {

			if (event.mouseButton.button == sf::Mouse::Right) {

				mouseScrollPressed_ = false;
				slowDirection_ = -releaseVelocity_;
				PhysicsUtil::Normalise(slowDirection_);
			}
		}
	}
	

}

