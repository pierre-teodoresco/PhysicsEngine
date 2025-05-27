#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @brief Abstract scene class
 */
class Scene
{
public:
    /**
     * @brief Render the scene
     * @param window application window
     */
    virtual void render(sf::RenderWindow &window) = 0;

    /**
     * @brief Update the scene
     * @param window application window
     * @param dt Delta time
     */
    virtual void update(sf::RenderWindow &window, float dt) = 0;

    virtual ~Scene() = default;
};