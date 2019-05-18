#pragma once

#include "pch.h"

class Renderer
{
public:
	Renderer();
	~Renderer();


	bool Init(sf::RenderWindow* newWindow = nullptr);
	void CleanUp();

	void StartRender(bool clear = true);
	void EndRender();

	void SetRenderWindow(sf::RenderWindow* newRenderWindow);
	void ClearRenderTarget();


	void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

private:

	sf::RenderWindow* window_;
};

