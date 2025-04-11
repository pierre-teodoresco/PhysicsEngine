#include "balistic.h"
#include <iostream>
#include <memory>

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
    auto isOutside = [&](const pe::Particle &p)
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
        pe::Vector3 clickPosition = {float(mousePos.x), float(mousePos.y), 0.0f};

        pe::Vector3 bottomLeftCorner = pe::Vector3(.0f, window.getSize().y, .0f);

        // get the vector from the bottom left corner of the window to the mouse position
        pe::Vector3 direction = clickPosition - bottomLeftCorner;

        // create an integrator for the particle
        auto integrator = std::make_shared<pe::Verlet>();

        // create a new particle at the bottom left corner of the window with a velocity in the direction of the mouse
        particles.emplace_back(pe::Particle(bottomLeftCorner, direction, pe::Vector3::zero(), 1.f, integrator));
    }

    wasMousePressed = isMousePressed;
}
