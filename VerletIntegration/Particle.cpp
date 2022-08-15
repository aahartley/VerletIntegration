#include "Particle.h"

void Particle::addConstraint(Constraint* c, int index) {
	constraints[index] = c;
}


void Particle::Update(float dt, float drag, sf::Vector2f& gravity, sf::Vector2f& lastMouseP, bool dragging, sf::Vector2f& mouseP, float elasticity) {
	if (dragging) {
		sf::Vector2f mouseSpeed = mouseP - lastMouseP;
		if (isInRadius(*this, mouseP, 20.0f)) {
			isSelected = true;
			for (Constraint* c : constraints) {
				if(c != nullptr)
					c->isSelected = true;

			}
			if (mouseSpeed.x > elasticity) mouseSpeed.x = elasticity;
			if (mouseSpeed.y > elasticity) mouseSpeed.y = elasticity;
			if (mouseSpeed.x < -elasticity) mouseSpeed.x = -elasticity;
			if (mouseSpeed.y < -elasticity) mouseSpeed.y = -elasticity;

			old_pos = pos - mouseSpeed;
		}
	}
	if (isPinned) {
		pos = init_pos;
		return;
	}
	sf::Vector2f newPos = pos + (pos - old_pos) * (1.0f - drag) + gravity * (1.0f - drag) * dt * dt;
	old_pos = pos;
	pos = newPos;
	//KeepInsideView(pos, old_pos);
}


void Particle::KeepInsideView(sf::Vector2f& pos, sf::Vector2f& old_pos) {
	if (pos.x >= 600) {
		pos.x = 600;
		old_pos.x = pos.x;

	}
	if (pos.y >= 560) {
		pos.y = 560;
		old_pos.y = pos.y;
	}
	if (pos.x < 0) {
		pos.x = 0;
		old_pos.x = pos.x;
	}
	if (pos.y < 0) {
		pos.y = 0;
		old_pos.y = pos.y;
	}

}