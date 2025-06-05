#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "RigidBody.hpp"

namespace pe
{
    /**
     * @brief The integrator class
     */
    class Integrator
    {
    public:
        virtual void integrate(std::vector<std::shared_ptr<RigidBody>> &bodies, float dt) = 0;
        virtual ~Integrator() = default;
    };

    /**
     * @brief The Euler integrator class
     */
    class EulerIntegrator : public Integrator
    {
    public:
        void integrate(std::vector<std::shared_ptr<RigidBody>> &bodies, float dt) override
        {
            for (const auto &body : bodies)
            {
                // Avoid useless integration of static bodies
                if (body->isStatic())
                {
                    // Reset accumulated force
                    body->accumulatedForce = Vector3::zero();
                    continue;
                }

                // Update acceleration based on accumulated force and inverse mass
                body->acceleration = body->accumulatedForce * body->inverseMass;

                // Update velocity using acceleration
                body->velocity += body->acceleration * dt;

                // Update position using velocity
                body->position += body->velocity * dt + body->acceleration * 0.5f * dt * dt;

                // Reset accumulated force after integration
                body->accumulatedForce = Vector3::zero();
            }
        }
    };

    /**
     * @brief The Verlet integrator class
     */
    class VerletIntegrator : public Integrator
    {
    public:
        void integrate(std::vector<std::shared_ptr<RigidBody>> &bodies, float dt) override
        {
            for (auto &body : bodies)
            {
                // Avoid useless integration of static bodies
                if (body->isStatic())
                {
                    // Reset accumulated force
                    body->accumulatedForce = Vector3::zero();
                    continue;
                }

                // Update acceleration based on accumulated force and inverse mass
                body->acceleration = body->accumulatedForce * body->inverseMass;

                const Vector3 temp = body->position;

                // Verlet position update
                body->position = body->position * 2.0f - body->oldPosition + body->acceleration * dt * dt;

                // Verlet velocity estimation (using current and previous position)
                body->velocity = (body->position - temp) / dt;

                body->oldPosition = temp;

                // Reset accumulated force after integration
                body->accumulatedForce = Vector3::zero();
            }
        }
    };
}