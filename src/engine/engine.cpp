#include "engine.h"

PhysicsEngine::PhysicsEngine()
    : window(sf::VideoMode({WIDTH, HEIGHT}), TITLE), p(Particle(Vector3(350, 100, 0)))
{
    window.setFramerateLimit(FPS);
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
    p.render(window);
    window.display();
}

void PhysicsEngine::update()
{
    p.addForce(Vector3(0, 9.81f, 0));
    p.integrate(DT);
}