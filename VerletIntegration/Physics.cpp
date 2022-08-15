#include "Physics.h"

Physics::Physics(float width, float height, float spacing, float startX, float startY) {
	//startX = 600 * 0.5f - width * spacing * 0.5f;
	//startY = 600 * 0.1f;
	//width /= spacing;
	//height /= spacing;
	for (int y = 0; y <= height; y++) {
		for (int x = 0; x <= width; x++) {
			Particle* p = new Particle(sf::Vector2f{ startX + x *spacing,startY + y *spacing });

			if (x != 0) {
				Particle* leftPoint = particles[this->particles.size() - 1];
				Constraint* c = new Constraint(*p, *leftPoint, spacing);
				leftPoint->addConstraint(c, 0);
				p->addConstraint(c, 0);
				constraints.push_back(c);
			}
			if (y != 0) {
				Particle* upPoint = particles[x + (y - 1) * (width + 1)];
				Constraint* c = new Constraint(*p, *upPoint, spacing);
				upPoint->addConstraint(c, 1);
				p->addConstraint(c, 1);
				constraints.push_back(c);
			}
			if (y == 0 && x % 2 == 0)
			{
				p->Pin();
			}

			particles.push_back(p);
		}
	}
}

void Physics::update(float dt, sf::Vector2f& lastMouseP, bool dragging, sf::Vector2f& mouseP) {
	for (auto& p : particles) {
	/*	float prevx = p->pos.x;
		float prevy = p->pos.y;
		p->pos.x = p->pos.x * 2 - p->old_pos.x + gravity.x * (dt * dt);
		p->pos.y = p->pos.y * 2 - p->old_pos.y + gravity.y * (dt * dt);
		p->old_pos.x = prevx;
		p->old_pos.y = prevy;
		keepInsideView(p->pos,p->old_pos);
		std::cout << "y: " << p->pos.y << '\n';*/
		p->Update(dt, drag, gravity, lastMouseP, dragging, mouseP,elasticity);
		

	}
	for (auto& c : constraints)
	{
		sf::Vector2f diff = getDifference(c->p1, c->p2);
		float diffFactor = (c->length - getLength(diff)) / getLength(diff) * 0.5;
		sf::Vector2f offset = { diff.x * diffFactor,  diff.y * diffFactor };

		c->p1.pos.x += offset.x;
		c->p1.pos.y += offset.y;
		c->p2.pos.x -= offset.x;
		c->p2.pos.y -= offset.y;
	}
}

