#pragma once

#include "collision/Collider.hpp"

// DEBUG
#include <SFML/Graphics.hpp>

namespace pe
{
    class BoxCollider : public Collider
    {
    public:
        float length, width, height, restitution;

        BoxCollider(float length, float width, float height, float restitution = 0.2f) : length(length), width(width), height(height), restitution(restitution) {}

        // Main double dispatch
        ContactManifold isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const override;

        // Collision Box vs Sphere
        ContactManifold isCollidingWithSphere(const SphereCollider &sphere, const RigidBody &self, const RigidBody &otherBody) const override;

        // Collision Box vs Box (AABB)
        ContactManifold isCollidingWithBox(const BoxCollider &box, const RigidBody &self, const RigidBody &otherBody) const override;

        // DEBUG
        void draw(sf::RenderWindow &window, const pe::RigidBody &body) const;
    };

}
