#include "particle/particle.h"

void Particle::addForce(const Vector3 &force)
{
    acceleration += force * inverseMass;
}

void Particle::integrate(float dt)
{
    integrator->integrate(dt, position, velocity, acceleration);
}

void Particle::render(sf::RenderWindow &window) const
{
    sf::CircleShape shape(RADIUS);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2(position.getX(), position.getY()));
    window.draw(shape);
}

Vector3 Particle::getPosition() const
{
    return position;
}

Vector3 Particle::getVelocity() const
{
    return velocity;
}

Vector3 Particle::getAcceleration() const
{
    return acceleration;
}

float Particle::getMass() const
{
    return 1.0f / inverseMass;
}

void Particle::setIntegrator(std::shared_ptr<Integrator> i)
{
    this->integrator = i;
}
