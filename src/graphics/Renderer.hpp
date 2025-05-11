#include <SFML/Graphics.hpp>
#include "core/RigidBody.hpp"

class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void draw(sf::RenderWindow &window, const pe::RigidBody &body) = 0;
};