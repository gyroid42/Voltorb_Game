#pragma once


#include "pch.h"

class PhysicsUtil
{
public:
	PhysicsUtil();
	~PhysicsUtil();

	static float DistanceToSqr(const sf::Vector2<float>& pos1, const sf::Vector2<float>& pos2);
	static float VectorLengthSqr(const sf::Vector2f& vector);
	static sf::Vector2<float> VectorBetween(const sf::Vector2<float>& pos1, const sf::Vector2<float>& pos2);

	static float Normalise(sf::Vector2<float>& vector);

	static const float G;
	static const float pi;
	static const float dampeningFactor;
};

