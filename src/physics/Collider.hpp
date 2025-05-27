#pragma once

#include "maths/Vector3.hpp"

namespace pe
{
    class RigidBody; // forward declaration

    struct ContactManifold
    {
        bool colliding = false;
        Vector3 contactPoint;
        Vector3 normal;
        float penetration = 0.0f;
        float restitution = 0.0f;
    };

    class Collider
    {
    public:
        virtual ~Collider() = default;

        // Double dispatch: generic collision test

        /**
         * @brief Test if this collider is colliding with another collider
         * @param other The other collider to test against
         * @param self The RigidBody that owns this collider
         * @param otherBody The RigidBody that owns the other collider
         * @return true if colliding, false otherwise
         */
        virtual ContactManifold isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const = 0;

        // Double dispatch: specific collision tests

        /**
         * @brief Test if this collider is colliding with a SphereCollider
         * @param sphere The SphereCollider to test against
         * @param self The RigidBody that owns this collider
         * @param otherBody The RigidBody that owns the SphereCollider
         * @return true if colliding, false otherwise
         */
        virtual ContactManifold isCollidingWithSphere(const class SphereCollider &sphere, const RigidBody &self, const RigidBody &otherBody) const = 0;

        /**
         * @brief Test if this collider is colliding with a BoxCollider
         * @param box The BoxCollider to test against
         * @param self The RigidBody that owns this collider
         * @param otherBody The RigidBody that owns the BoxCollider
         * @return true if colliding, false otherwise
         */
        virtual ContactManifold isCollidingWithBox(const class BoxCollider &box, const RigidBody &self, const RigidBody &otherBody) const = 0;
    };
}