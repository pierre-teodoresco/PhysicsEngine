#include "engine.h"

PhysicsEngine::PhysicsEngine()
    : window(sf::VideoMode({WIDTH, HEIGHT}), TITLE)
{
    window.setFramerateLimit(FPS);
    particles.push_back(Particle(Vector3(350, 200, 0), Vector3::zero(), Vector3::zero(), 1.0f, 0.8f, Particle::Integrator::Euler));
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::run()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        update();
        render();
    }
}

void PhysicsEngine::render()
{
    window.clear(sf::Color::Black);
    for (const auto &p : particles)
    {
        p.render(window);
    }
    window.display();
}

void PhysicsEngine::update()
{
    for (auto &p : particles)
    {
        p.addForce(Vector3(0, 9.81f, 0));
        p.integrate(DT);
    }
}