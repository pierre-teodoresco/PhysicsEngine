#include "particle/particle.h"

Particle::Particle(Vector3 position, float mass, float damping, Integrator integrator)
    : position(position), inverseMass(1.0f / mass), damping(damping), integrator(integrator)
{
    velocity = Vector3();
    acceleration = Vector3();
}

Particle::~Particle()
{
}

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

void Particle::render(sf::RenderWindow &window)
{
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(sf::Vector2(position.x, position.y));
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

void Particle::setIntegration(Integrator integrator)
{
    this->integrator = integrator;
}

void Particle::euler(float dt)
{
    // Update velocity using acceleration
    velocity += acceleration * dt * damping;

    // Update position using velocity
    position += velocity * dt + acceleration * 0.5 * dt * dt;
}

void Particle::verlet(float dt)
{
    // TODO
}