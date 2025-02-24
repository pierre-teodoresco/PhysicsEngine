#include "particle/particle.h"

void Particle::addForce(const Vector3 &force)
{
    acceleration += force * inverseMass;
}

void Particle::integrate(float dt)
{
    switch (integrator)
    {
    case Integrator::Euler:
        euler(dt);
        break;
    case Integrator::Verlet:
        verlet(dt);
        break;
    }
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

void Particle::setIntegration(Integrator i)
{
    this->integrator = i;
}

void Particle::euler(float dt)
{
    // Update velocity using acceleration
    velocity += acceleration * dt * damping;

    // Update position using velocity
    position += velocity * dt + acceleration * 0.5f * dt * dt;
}

void Particle::verlet(float dt)
{
    if (firstFrame)
    {
        // If it's the first frame, we need to initialize the previous position
        oldPosition = position - velocity * dt;
    }

    Vector3 oldPos = position;

    // Update position using old position and acceleration
    position = position * 2.0f - oldPosition + acceleration * dt * dt;

    // Update velocity using new position
    velocity = (position - oldPosition) / (2.0f * dt);

    oldPosition = oldPos;
}