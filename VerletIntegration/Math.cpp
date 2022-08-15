#include "Math.h"
float getDistance(Particle& p1, Particle& p2) {
    float dx = p1.pos.x - p2.pos.x;
    float dy = p1.pos.y - p2.pos.y;
    return std::sqrt(dx * dx + dy * dy);
}

float getLength(sf::Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f getDifference(Particle& p1, Particle& p2) {
    return sf::Vector2f(p1.pos.x - p2.pos.x, p1.pos.y - p2.pos.y);
}

bool isInRadius(const Particle& p, sf::Vector2f& center, float radius)
{
    const sf::Vector2f v = p.pos - center;
    return v.x * v.x + v.y * v.y < radius* radius;
}