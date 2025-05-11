#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @brief Abstract game class
 */
class Game
{
public:
    /**
     * @brief Render the game
     * @param window application window
     */
    virtual void render(sf::RenderWindow &window) = 0;

    /**
     * @brief Update the game
     * @param window application window
     * @param dt Delta time
     */
    virtual void update(sf::RenderWindow &window, float dt) = 0;

    virtual ~Game() = default;
};