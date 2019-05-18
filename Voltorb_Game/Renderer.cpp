
#include "pch.h"

#include "Renderer.h"


Renderer::Renderer() :
	window_(nullptr)
{
}


Renderer::~Renderer()
{
}


bool Renderer::Init(sf::RenderWindow* newWindow) {

	window_ = newWindow;


	return true;
}

void Renderer::CleanUp() {


}


void Renderer::StartRender(bool clear) {


	if (clear) {

		window_->clear();
	}


}


void Renderer::EndRender() {

	window_->display();
}


void Renderer::SetRenderWindow(sf::RenderWindow* newRenderWindow) {

	window_ = newRenderWindow;

}


void Renderer::ClearRenderTarget() {

	window_ = nullptr;
}


void Renderer::Draw(const sf::Drawable& drawable, const sf::RenderStates& states) {

	if (window_) {

		window_->draw(drawable, states);
	}
}

