#pragma once

#include <vector>
#include <memory>
#include "core/RigidBody.hpp"

namespace pe
{
    class CollisionManager
    {
    public:
        /**
         * @brief Detect and resolve collisions between all bodies
         * @param bodies vector of shared pointers to RigidBody
         */
        static void detectAndResolveCollisions(std::vector<std::shared_ptr<RigidBody>> &bodies)
        {
            for (size_t i = 0; i < bodies.size(); ++i)
            {
                for (size_t j = i + 1; j < bodies.size(); ++j)
                {
                    auto &a = bodies[i];
                    auto &b = bodies[j];
                    if (a->collider && b->collider)
                    {
                        if (a->collider->isColliding(*b->collider, *a, *b))
                        {
                            // Appeler la résolution ici, ex :
                            CollisionManager::resolveCollision(*a, *b);
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
         */
        static void resolveCollision(RigidBody &a, RigidBody &b)
        {
            // Basic elastic collision resolution for two bodies

            // If both bodies are static, do nothing
            if (a.isStatic() && b.isStatic())
                return;

            // Calculate the direction of collision (from a to b)
            Vector3 normal = b.position - a.position;
            float distance = normal.norm();

            // Prevent division by zero
            if (distance == 0.0f)
                return;

            normal = normal / distance; // Normalize

            // Calculate relative velocity
            Vector3 relativeVelocity = b.velocity - a.velocity;

            // Calculate velocity along the normal
            float velocityAlongNormal = relativeVelocity.dot(normal);

            // If velocities are separating, do nothing
            if (velocityAlongNormal > 0)
                return;

            // Coefficient of restitution (elasticity)
            float restitution = 1.0f; // 1.0 = perfectly elastic, 0.0 = perfectly inelastic

            // Calculate impulse scalar
            float invMassA = a.inverseMass;
            float invMassB = b.inverseMass;

            float impulseScalar = -(1.0f + restitution) * velocityAlongNormal;
            float invMassSum = invMassA + invMassB;
            if (invMassSum == 0.0f)
                return; // Both infinite mass

            impulseScalar /= invMassSum;

            Vector3 impulse = normal * impulseScalar;

            // Apply impulse to velocities
            if (!a.isStatic())
                a.velocity -= impulse * invMassA;
            if (!b.isStatic())
                b.velocity += impulse * invMassB;

            // Optional: Positional correction to prevent sinking
            const float percent = 0.2f; // usually 20% to 80%
            const float slop = 0.01f;   // Penetration allowance
            float penetration = 0.0f;
            if (distance < slop)
                penetration = slop - distance;
            if (penetration > 0.0f)
            {
                Vector3 correction = normal * (penetration / invMassSum) * percent;
                if (!a.isStatic())
                    a.position -= correction * invMassA;
                if (!b.isStatic())
                    b.position += correction * invMassB;
            }
        }
    };
}
