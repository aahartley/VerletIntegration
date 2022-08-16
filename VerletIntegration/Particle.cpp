#include "Particle.h"

void Particle::addConstraint(Constraint* c, int index) {
	constraints[index] = c;
}


void Particle::Update(float dt, float drag, sf::Vector2f& gravity, sf::Vector2f& lastMouseP, bool dragging, sf::Vector2f& mouseP, float elasticity, bool tearing, sf::Vector2f& tearMP) {
	if (dragging) {

		if (isInRadius(*this, lastMouseP, 20.0f)) {
			isSelected = true;
			sf::Vector2f mouseSpeed = mouseP - lastMouseP;
			mouseSpeed.x /= 6;
			mouseSpeed.y /= 6;
			//std::cout << "last " << lastMouseP.x << " curr " << mouseP.x << '\n';
			//std::cout << mouseSpeed.x << '\n';
			for (Constraint* c : constraints) {
				if(c != nullptr)
					c->isSelected = true;

			}
			if (mouseSpeed.x > elasticity) mouseSpeed.x = elasticity;
			if (mouseSpeed.y > elasticity ) mouseSpeed.y = elasticity;
			if (mouseSpeed.x < -elasticity ) mouseSpeed.x = -elasticity;
			if (mouseSpeed.y < -elasticity ) mouseSpeed.y = -elasticity;

			old_pos = pos - mouseSpeed;
		}
	}
	if (tearing)
	{
		if (isInRadius(*this, tearMP, 10.0f)) {

			for (Constraint* c : constraints)
			{
				if (c != nullptr)
					c->Break();
			}
		}
	}
	if (isPinned) {
		pos = init_pos;
		return;
	}
	sf::Vector2f newPos = pos + (pos - old_pos) * (1.0f - drag) + gravity * (1.0f - drag) * dt * dt;
	old_pos = pos;
	pos = newPos;
	KeepInsideView(pos, old_pos);

}


void Particle::KeepInsideView(sf::Vector2f& pos, sf::Vector2f& old_pos) {
	if (pos.x >= 800) {
		pos.x = 800;
		old_pos.x = pos.x;

	}
	if (pos.y >= 800) {
		pos.y = 800;
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