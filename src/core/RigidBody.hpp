#pragma once

#include "maths/Vector3.hpp"
#include <memory>
#include "graphics/Renderer.hpp"

namespace pe
{

    /**
     * @brief The RigidBody class
     */
    class RigidBody
    {
    public:
        RigidBody() = default;

        RigidBody(Vector3 position, Vector3 velocity, Vector3 acceleration, float mass)
            : position(position),
              velocity(velocity),
              acceleration(acceleration),
              inverseMass(1.0f / mass) {};

        ~RigidBody() = default;

        /**
         * @brief Compute the force applied to the RigidBody
         * @param force The force applied to the RigidBody
         */
        void applyForce(const Vector3 &force)
        {
            acceleration += force * inverseMass;
        }

        /**
         * @brief Get the mass of the RigidBody
         * @return The mass of the RigidBody
         */
        [[nodiscard]] float getMass() const
        {
            return 1.0f / inverseMass;
        }

        /**
         * @brief True if the body is static (can't be moved)
         * @return true / false based on inverse mass
         */
        bool isStatic() const
        {
            const float EPSILON = 1e-6f;
            return std::fabs(inverseMass) < EPSILON;
        }

        /**
         * @brief Set a renderer to the body
         * @param renderer smart pointer to the new renderer for the body
         */
        void setRenderer(std::unique_ptr<Renderer> renderer)
        {
            this->renderer = std::move(renderer);
        }

    public:
        Vector3 position{};
        Vector3 velocity{};
        Vector3 acceleration{};
        float inverseMass{1.f};

        std::unique_ptr<Renderer> renderer = nullptr;
    };
}