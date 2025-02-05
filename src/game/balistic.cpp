#include "balistic.h"
#include <iostream>

void Balistic::render(sf::RenderWindow &window)
{
    // render the particles
    for (const auto &p : particles)
    {
        p.render(window);
    }
}

void Balistic::update(sf::RenderWindow &window, float dt)
{
    gatherMouseInput(window);

    // update the particles
    for (auto &p : particles)
    {
        p.addForce(GRAVITY);
        p.integrate(dt);
    }

    // remove particles that are out of the window
    auto isOutside = [&](const Particle &p)
    {
        return (p.getPosition().getX() > window.getSize().x ||
                p.getPosition().getY() > window.getSize().y);
    };

    particles.erase(std::remove_if(particles.begin(), particles.end(), isOutside), particles.end());

    // print the number of particles
    std::cout << "Number of particles: " << particles.size() << std::endl;
}

void Balistic::gatherMouseInput(sf::RenderWindow &window)
{
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // gather mouse input
    if (isMousePressed && !wasMousePressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        Vector3 clickPosition = {float(mousePos.x), float(mousePos.y), 0.0f};

        Vector3 bottomLeftCorner = Vector3(0.0f, window.getSize().y, 0.0f);

        // get the vector from the bottom left corner of the window to the mouse position
        Vector3 direction = clickPosition - bottomLeftCorner;

        // create a new particle at the bottom left corner of the window with a velocity in the direction of the mouse
        particles.push_back(Particle(bottomLeftCorner, direction, Vector3::zero(), 1.0f, 0.8f, Particle::Integrator::Verlet));
    }

    wasMousePressed = isMousePressed;
}