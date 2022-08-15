#pragma once
class Particle;
struct Constraint {

	Particle& p1;
	Particle& p2;
	float length;
	bool isActive = true;
	bool isSelected = false;

	Constraint(Particle& p1, Particle& p2, float length) :p1(p1), p2(p2), length(length) {}
	


}; 