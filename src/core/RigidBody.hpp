#pragma once

#include "maths/Vector3.hpp"
#include "graphics/Renderer.hpp"
#include <memory>

namespace pe
{
    class Collider; // forward declaration

    /**
     * @brief The RigidBody class
     */
    class RigidBody
    {
    public:
        RigidBody(Vector3 position, Vector3 velocity, Vector3 acceleration, float mass = -1.0f);

        /**
         * @brief Compute the force applied to the RigidBody
         * @param force The force applied to the RigidBody
         */
        void applyForce(const Vector3 &force);

        /**
         * @brief Get the mass of the RigidBody
         * @return The mass of the RigidBody
         */
        [[nodiscard]] float getMass() const;

        /**
         * @brief True if the body is static (can't be moved)
         * @return true / false based on inverse mass
         */
        bool isStatic() const;

        /**
         * @brief Make the body static (can't be moved)
         */
        void makeStatic();
        /**
         * @brief Set a collider to the body
         * @param collider unique pointer to the new collider for the body
         */
        void setCollider(std::unique_ptr<Collider> c);
        /**
         * @brief Set a renderer to the body
         * @param renderer unique pointer to the new renderer for the body
         */
        void setRenderer(std::unique_ptr<Renderer> r);

    public:
        Vector3 position{};
        Vector3 velocity{};
        Vector3 acceleration{};
        float inverseMass{1.f};

        std::unique_ptr<Collider> collider;
        std::unique_ptr<Renderer> renderer;
    };
}