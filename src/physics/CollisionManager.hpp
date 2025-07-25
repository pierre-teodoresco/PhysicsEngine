#pragma once

#include <vector>
#include <memory>
#include "RigidBody.hpp"
#include "Collider.hpp"

// Debug
#include <iostream>

namespace pe
{
    class CollisionManager
    {
    public:
        /**
         * @brief Detect and resolve collisions between all bodies
         * @param bodies vector of shared pointers to RigidBody
         */
        static void detectAndResolveCollisions(const std::vector<std::shared_ptr<RigidBody>> &bodies)
        {
            for (size_t i = 0; i < bodies.size(); ++i)
            {
                for (size_t j = i + 1; j < bodies.size(); ++j)
                {
                    const auto &a = bodies[i];
                    const auto &b = bodies[j];
                    if (a->collider && b->collider)
                    {
                        auto contact = a->collider->isColliding(*b->collider, *a, *b);
                        if (contact.colliding)
                        {
                            // DEBUG: Print collision information
                            std::cout << "Collision detected between body " << i << " and body " << j << std::endl;

                            CollisionManager::resolveCollision(*a, *b, contact);
                        }
                    }
                }
            }
        }

    private:
        /**
         * @brief Resolve a collision between two bodies
         * @param a RigidBody
         * @param b RigidBody
         * @param contact ContactManifold containing collision information
         */
        static void resolveCollision(RigidBody &a, RigidBody &b, const ContactManifold &contact)
        {
            /* === Resolve only if necessary === */
            // If there is no collision, do nothing
            if (!contact.colliding)
                return;

            // If both bodies are static, do nothing
            if (a.isStatic() && b.isStatic())
                return;

            /* === Impulse-based resolution === */
            // Calculate the relative velocity
            Vector3 relativeVelocity = a.velocity - b.velocity;
            const float relativeVelocityAlongNormal = relativeVelocity.dot(contact.normal);
            const float impulseMagnitude = (1.f + contact.restitution) * relativeVelocityAlongNormal / (a.inverseMass + b.inverseMass);
            const Vector3 impulse = contact.normal * impulseMagnitude;

            a.velocity -= impulse * a.inverseMass;
            b.velocity += impulse * b.inverseMass;

            /* === Position correction === */

            // Baumgarte
            const float percent = 0.8f; // between 20% and 80%
            const float slop = 0.01f;   // slop to avoid jittering

            if (const float penetration = contact.penetration - slop; penetration > 0.0f)
            {
                const Vector3 correction = contact.normal * (penetration / (a.inverseMass + b.inverseMass)) * percent;
                if (!a.isStatic())
                    a.position -= correction * a.inverseMass;
                if (!b.isStatic())
                    b.position += correction * b.inverseMass;
            }
        }
    };
}
