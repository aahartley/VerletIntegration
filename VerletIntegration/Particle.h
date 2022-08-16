#pragma once
#include<SFML/Graphics.hpp>
#include "Constraint.h"
#include <iostream>
#include "Math.h"
class Particle {
private:
	Constraint* constraints[2] = { nullptr };

public:
	sf::Vector2f pos;
	sf::Vector2f old_pos;
	sf::Vector2f init_pos;
	bool isPinned = false;
	bool isSelected = false;
	Particle(sf::Vector2f pos) :pos(pos) { old_pos.x = pos.x; old_pos.y = pos.y; init_pos.x = pos.x; init_pos.y = pos.y; }

	void addConstraint(Constraint* c, int index);
	void Pin() { isPinned = true; };
	void KeepInsideView(sf::Vector2f& pos, sf::Vector2f& old_pos);
	void Update(float dt, float drag, sf::Vector2f& gravity, sf::Vector2f& lastMouseP, bool dragging, sf::Vector2f& mouseP, float elasticity, bool tearing, sf::Vector2f& tearMP);


};


