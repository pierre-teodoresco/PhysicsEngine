#pragma once

#include "Renderer.hpp"
#include "physics/RigidBody.hpp"
#include <SFML/Graphics.hpp>

class RectangleRenderer : public Renderer
{
public:
    RectangleRenderer(float length, float width, sf::Color color) : length(length), width(width), color(color) {};

    void draw(sf::RenderWindow &window, const pe::RigidBody &body) override
    {
        sf::RectangleShape shape(sf::Vector2f(length, width));
        shape.setFillColor(color);
        shape.setPosition(sf::Vector2f(body.position.getX(), body.position.getY()));
        window.draw(shape);
    }

private:
    float length, width;
    sf::Color color;
};