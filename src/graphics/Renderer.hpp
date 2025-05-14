#pragma once

#include <SFML/Graphics.hpp>

namespace pe
{
    class RigidBody; // Forward declaration
}

class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void draw(sf::RenderWindow &window, const pe::RigidBody &body) = 0;
};