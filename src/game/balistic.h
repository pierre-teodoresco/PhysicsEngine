#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include "particle/particle.h"
#include "vector3/vector3.h"
#include "force/particleForce.h"

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

    std::vector<std::shared_ptr<pe::Particle>> particles;
    pe::ParticleForceRegistry forceRegitry;
    std::shared_ptr<pe::ParticleGravity> gravity = std::make_shared<pe::ParticleGravity>();
    bool wasMousePressed = false; // allow to avoid creating multiple particles when the mouse button is held
};