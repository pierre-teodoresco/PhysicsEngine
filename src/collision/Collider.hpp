#pragma once

#include "core/RigidBody.hpp"

namespace pe
{
    class Collider
    {
    public:
        virtual ~Collider() = default;

        /**
         * @brief Check if the collider is colliding with another collider
         * @param other The other collider
         * @param self The rigid body of the current collider
         * @param otherBody The rigid body of the other collider
         * @return true if the colliders are colliding, false otherwise
         */
        virtual bool isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const = 0;
    };
}
