#pragma once

#include <SFML/Graphics.hpp>
#include "particle/particle.h"

/**
 * @brief The main application class
 */
class PhysicsEngine
{
public:
    PhysicsEngine();
    ~PhysicsEngine();

    /**
     * @brief Run the application
     */
    void run();

    static constexpr auto TITLE = "Physics Engine";
    static constexpr auto WIDTH = 800u;
    static constexpr auto HEIGHT = 600u;
    static constexpr auto FPS = 60u;
    static constexpr auto DT = 1.0f / FPS;

private:
    /**
     * @brief Render the window
     */
    void render();

    /**
     * @brief Update the window
     */
    void update();

    sf::RenderWindow window;
    Particle p;
};
