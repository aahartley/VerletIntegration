#pragma once
#include "Physics.h"
float getDistance(Particle& p1, Particle& p2);
float getLength(sf::Vector2f& v);
sf::Vector2f getDifference(Particle& p1, Particle& p2);
bool isInRadius(const Particle& p, sf::Vector2f& center, float radius);

