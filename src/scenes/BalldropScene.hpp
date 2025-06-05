#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Scene.hpp"
#include "physics/RigidBody.hpp"
#include "maths/Vector3.hpp"
#include "physics/Force.hpp"
#include "physics/Integrator.hpp"

/**
 * @brief Demo game that simulates a ballistic trajectory of particles
 */
class Balldrop : public Scene
{
public:
    Balldrop();

    void render(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window, float dt) override;

private:
    /**
     * @brief Gather mouse input
     * @param window application window
     */
    void gatherMouseInput(const sf::RenderWindow& window);

    std::vector<std::shared_ptr<pe::RigidBody>> bodies;
    pe::ForceRegistry forceRegistry;
    std::shared_ptr<pe::StaticFriction> staticFriction = std::make_shared<pe::StaticFriction>(0.3f);
    std::shared_ptr<pe::KineticFriction> kineticFriction = std::make_shared<pe::KineticFriction>(0.1f);
    std::shared_ptr<pe::Gravity> gravity = std::make_shared<pe::Gravity>();
    std::unique_ptr<pe::Integrator> integrator = std::make_unique<pe::EulerIntegrator>();
    bool wasMousePressed = false; // allow to avoid creating multiple particles when the mouse button is held
};