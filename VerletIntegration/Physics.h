#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include "Particle.h"
#include "Math.h"



class Physics {
public:
	std::vector<Particle*> particles;
	std::vector<Constraint*> constraints;
	sf::Vector2f gravity = { 0.0f,15.0f }; //25
	float drag = 0.01f;
	float elasticity =20.0f;
	Physics();
	Physics(float width, float height, float spacing, float startX, float startY);
	void update(float dt, sf::Vector2f& lastMouseP, bool& dragging, sf::Vector2f& mouseP, bool& tearing, sf::Vector2f& tearMP);

};