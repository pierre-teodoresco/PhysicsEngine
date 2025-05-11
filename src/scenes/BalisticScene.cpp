#include "BalisticScene.hpp"
#include <iostream>
#include <memory>

void Balistic::render(sf::RenderWindow &window)
{
    // render the particles
    for (const auto &rb : bodies)
    {
        rb->renderer->draw(window);
    }
}

void Balistic::update(sf::RenderWindow &window, float dt)
{
    gatherMouseInput(window);

    // update the rbs
    for (auto &rb : bodies)
    {
        forceRegitry.add(rb, gravity);
        forceRegitry.updateForces(dt);
    }
    integrator->integrate(bodies, dt);

    // clear registry
    forceRegitry.clear();

    // remove bodies that are out of the window
    auto isOutside = [&](const std::shared_ptr<pe::RigidBody> rb)
    {
        return (rb->getPosition().getX() > window.getSize().x ||
                rb->getPosition().getY() > window.getSize().y);
    };

    bodies.erase(std::remove_if(bodies.begin(), bodies.end(), isOutside), bodies.end());

    // print the number of bodies
    std::cout << "Number of bodies: " << bodies.size() << std::endl;
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

        // create a new rigidbody at the bottom left corner of the window with a velocity in the direction of the mouse
        pe::RigidBody rb(bottomLeftCorner, direction, pe::Vector3::zero(), 1.f);
        rb.setRenderer(std::make_unique<CircleRenderer>(5.f, sf::Color::White));
        particles.emplace_back(std::make_shared<pe::RigidBody>(rb));
    }

    wasMousePressed = isMousePressed;
}
