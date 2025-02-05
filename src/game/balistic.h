#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "game.h"
#include "particle/particle.h"
#include "vector3/vector3.h"

/**
 * @brief Demo game that simulates a balistic trajectory of particles
 */
class Balistic : public Game
{
public:
    void render(sf::RenderWindow &window);
    void update(sf::RenderWindow &window, float dt);

    static constexpr Vector3 GRAVITY = {0, 9.81f, 0};

private:
    void gatherMouseInput(sf::RenderWindow &window);

    std::vector<Particle> particles;
    bool wasMousePressed = false; // allow to avoid creating multiple particles when the mouse button is held
};