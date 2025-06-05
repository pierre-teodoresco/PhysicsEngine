#include "BalisticScene.hpp"
#include <iostream>
#include <memory>
#include "physics/CollisionManager.hpp"
#include "physics/SphereCollider.hpp"
#include "graphics/CircleRenderer.hpp"

void Balistic::render(sf::RenderWindow &window)
{
    // render the particles
    for (const auto &rb : bodies)
    {
        rb->renderer->draw(window, *rb);
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

    pe::CollisionManager::detectAndResolveCollisions(bodies);

    // remove bodies that are out of the window
    auto isOutside = [&](const std::shared_ptr<pe::RigidBody> rb)
    {
        return (rb->position.getX() > window.getSize().x ||
                rb->position.getY() > window.getSize().y);
    };

    bodies.erase(std::remove_if(bodies.begin(), bodies.end(), isOutside), bodies.end());

    // print the number of bodies
    std::cout << "Number of bodies: " << bodies.size() << std::endl;
}

void Balistic::gatherMouseInput(const sf::RenderWindow& window)
{
    const bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // gather mouse input
    if (isMousePressed && !wasMousePressed)
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const pe::Vector3 clickPosition{static_cast<float>(mousePos.x), static_cast<float>(mousePos.y), 0.0f};

        pe::Vector3 bottomLeftCorner{.0f, static_cast<float>(window.getSize().y), .0f};

        // get the vector from the bottom left corner of the window to the mouse position
        const pe::Vector3 direction = clickPosition - bottomLeftCorner;

        // create a new rigidbody at the bottom left corner of the window with a velocity in the direction of the mouse
        auto rb = std::make_shared<pe::RigidBody>(bottomLeftCorner, direction, pe::Vector3::zero(), 1.f);
        rb->setCollider(std::make_unique<pe::SphereCollider>(50.f));
        rb->setRenderer(std::make_unique<CircleRenderer>(50.f, sf::Color::White));

        bodies.emplace_back(rb);
    }

    wasMousePressed = isMousePressed;
}
