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
            for (auto &body : bodies)
            {
                // Avoid useless integration of static bodies
                if (body->isStatic())
                    continue;

                // Update velocity using acceleration
                body->velocity += body->acceleration * dt;

                // Update position using velocity
                body->position += body->velocity * dt + body->acceleration * 0.5f * dt * dt;
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
                    continue;

                auto &init = initialized[body.get()];
                auto &oldPos = oldPositions[body.get()];

                if (!init)
                {
                    oldPos = body->position - body->velocity * dt;
                    init = true;
                }

                Vector3 temp = body->position;

                // Verlet position update
                body->position = body->position * 2.0f - oldPos + body->acceleration * dt * dt;

                // Verlet velocity estimation
                body->velocity = (body->position - oldPos) / (2.0f * dt);

                oldPos = temp;
            }
        }

    private:
        std::unordered_map<RigidBody *, Vector3> oldPositions;
        std::unordered_map<RigidBody *, bool> initialized;
    };
}