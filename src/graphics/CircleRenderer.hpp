#pragma once

#include "Renderer.hpp"
#include "physics/RigidBody.hpp"
#include <SFML/Graphics.hpp>

class CircleRenderer : public Renderer
{
public:
    CircleRenderer(float radius, sf::Color color) : radius(radius), color(color) {};

    void draw(sf::RenderWindow &window, const pe::RigidBody &body) override
    {
        sf::CircleShape shape(radius);
        shape.setFillColor(color);
        shape.setOrigin(sf::Vector2f(radius, radius)); // Set origin to center of circle
        shape.setPosition(sf::Vector2f(body.position.getX(), body.position.getY()));
        window.draw(shape);
    }

private:
    float radius;
    sf::Color color;
};