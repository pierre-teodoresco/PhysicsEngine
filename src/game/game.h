#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @brief Abstract game class
 */
class Game
{
public:
    virtual void render(sf::RenderWindow &window) = 0;
    virtual void update(sf::RenderWindow &window, float dt) = 0;
};