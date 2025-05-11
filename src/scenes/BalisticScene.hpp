#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.hpp"
#include "core/RigidBody.hpp"
#include "maths/Vector3.hpp"
#include "core/Force.hpp"
#include "core/Integrator.hpp"

/**
 * @brief Demo game that simulates a balistic trajectory of particles
 */
class Balistic : public Game
{
public:
    void render(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window, float dt) override;

private:
    /**
     * @brief Gather mouse input
     * @param window application window
     */
    void gatherMouseInput(sf::RenderWindow &window);

    std::vector<std::shared_ptr<pe::RigidBody>> bodies;
    pe::RigidBodyForceRegistry forceRegitry;
    std::unique_ptr<pe::RigidBodyGravity> gravity = std::make_unique<pe::RigidBodyGravity>();
    std::unique_ptr<pe::Integrator> integrator = std::make_unique<pe::EulerIntegrator>();
    bool wasMousePressed = false; // allow to avoid creating multiple particles when the mouse button is held
};