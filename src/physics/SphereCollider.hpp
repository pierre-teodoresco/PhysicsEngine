#pragma once

#include "Collider.hpp"

// DEBUG
#include <SFML/Graphics.hpp>

namespace pe
{
    class SphereCollider : public Collider
    {
    public:
        float radius, restitution;

        SphereCollider(float radius, float restitution = 0.8f) : radius(radius), restitution(restitution) {}

        // Double dispatch principal
        [[nodiscard]] ContactManifold isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const override;

        // Collision Sphere vs Sphere
        [[nodiscard]] ContactManifold isCollidingWithSphere(const SphereCollider &sphere, const RigidBody &self, const RigidBody &otherBody) const override;

        // Collision Sphere vs Box
        [[nodiscard]] ContactManifold isCollidingWithBox(const BoxCollider &box, const RigidBody &self, const RigidBody &otherBody) const override;

        // DEBUG
        void draw(sf::RenderWindow &window, const pe::RigidBody &body) const;
    };
}