#pragma once

#include "collision/Collider.hpp"

namespace pe
{
    class CircleCollider : public Collider
    {
    public:
        float radius;

        /**
         * @brief Construct a new Circle Collider object
         * @param radius The radius of the circle
         */
        CircleCollider(float radius) : radius(radius) {}

        bool isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const override
        {
            // Try dynamic_cast to check if the other collider is a CircleCollider
            const CircleCollider *otherCircle = dynamic_cast<const CircleCollider *>(&other);
            if (otherCircle)
            {
                // Circle vs Circle collision
                // Get the distance between the centers
                float dist = (self.position - otherBody.position).norm();
                // If the distance is less than the sum of the radii, they are colliding
                return dist < (radius + otherCircle->radius);
            }
            // If not a CircleCollider, we don't know how to check collision
            return false;
        }
    };
}