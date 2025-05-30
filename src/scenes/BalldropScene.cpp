#include "BalldropScene.hpp"
#include <iostream>
#include <memory>
#include "physics/CollisionManager.hpp"
#include "physics/SphereCollider.hpp"
#include "physics/BoxCollider.hpp"
#include "graphics/CircleRenderer.hpp"
#include "graphics/RectangleRenderer.hpp"

Balldrop::Balldrop()
{
    // create a ground
    auto ground = std::make_shared<pe::RigidBody>(pe::Vector3(1000.f * 0.2f, 800.f * 0.9f, 0.f), pe::Vector3(0.f, 0.f, 0.f), pe::Vector3(0.f, 0.f, 0.f));
    ground->makeStatic(); // make the ground static
    ground->setCollider(std::make_unique<pe::BoxCollider>(1000.f * 0.6f, 50.f, 0.f));
    ground->setRenderer(std::make_unique<RectangleRenderer>(1000.f * 0.6f, 50.f, sf::Color::Green));
    bodies.emplace_back(ground);
}

void Balldrop::render(sf::RenderWindow &window)
{
    // render the particles
    for (const auto &rb : bodies)
    {
        rb->renderer->draw(window, *rb);

        // DEBUG: draw the position of the rigid body
        sf::CircleShape positionMarker(5.f);
        positionMarker.setFillColor(sf::Color::Red);
        positionMarker.setPosition(sf::Vector2f(rb->position.getX() - 5.f, rb->position.getY() - 5.f));
        window.draw(positionMarker);

        // DEBUG: draw the collider
        if (rb->collider)
        {
            if (auto sphereCollider = dynamic_cast<pe::SphereCollider *>(rb->collider.get()))
            {
                sphereCollider->draw(window, *rb);
            }
            else if (auto boxCollider = dynamic_cast<pe::BoxCollider *>(rb->collider.get()))
            {
                boxCollider->draw(window, *rb);
            }
        }
    }
}

void Balldrop::update(sf::RenderWindow &window, float dt)
{
    /* INPUTS */
    gatherMouseInput(window);

    /* INTEGRATION */
    // update the rbs
    for (auto &rb : bodies)
    {
        forceRegitry.add(rb, gravity);
        forceRegitry.add(rb, kineticFriction);
        forceRegitry.add(rb, staticFriction);
        forceRegitry.updateForces(dt);
    }

    // clear the force registry
    forceRegitry.clear();

    // integrate the bodies
    integrator->integrate(bodies, dt);

    /* COLLISIONS */
    pe::CollisionManager::detectAndResolveCollisions(bodies);

    /* OPTIMISATION */
    // remove bodies that are out of the window
    auto isOutside = [&](const std::shared_ptr<pe::RigidBody> rb)
    {
        return (rb->position.getX() > window.getSize().x ||
                rb->position.getY() > window.getSize().y);
    };
    bodies.erase(std::remove_if(bodies.begin(), bodies.end(), isOutside), bodies.end());
}

void Balldrop::gatherMouseInput(sf::RenderWindow &window)
{
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // gather mouse input
    if (isMousePressed && !wasMousePressed)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        pe::Vector3 clickPosition{float(mousePos.x), float(mousePos.y), 0.0f};

        // create a new rigidbody at the mouse position
        auto rb = std::make_shared<pe::RigidBody>(clickPosition, pe::Vector3::zero(), pe::Vector3::zero(), 1.f);
        rb->setCollider(std::make_unique<pe::SphereCollider>(50.f));
        rb->setRenderer(std::make_unique<CircleRenderer>(50.f, sf::Color::White));

        bodies.emplace_back(rb);
    }

    wasMousePressed = isMousePressed;
}
