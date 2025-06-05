#pragma once

#include <memory>
#include <vector>
#include "RigidBody.hpp"
#include "PhysicsConstants.hpp"

namespace pe
{
    /**
     * @brief Interface of a force for a RigidBody
     */
    class ForceGenerator
    {
    public:
        ForceGenerator() = default;
        virtual ~ForceGenerator() = default;

        /**
         * @brief Apply a force to a RigidBody
         * @param rb RigidBody on which the force is applied
         * @param duration duration of the frame
         */
        virtual void updateForce(const std::shared_ptr<RigidBody>& rb, float duration) const = 0;
    };

    /**
     * @brief Manage which force is apply to which RigidBody of the system
     */
    class ForceRegistry
    {
    public:
        struct ForceRegistration
        {
            std::shared_ptr<RigidBody> rb;
            std::shared_ptr<ForceGenerator> fg;
        };

        using Registry = std::vector<ForceRegistration>;

        /**
         * @brief Add a RigidBody and its force generator to the registry
         * @param rb RigidBody
         * @param fg Force generator
         */
        void add(std::shared_ptr<RigidBody> rb, std::shared_ptr<ForceGenerator> fg);

        /**
         * @brief Remove a RigidBody and its force generator from the registry
         * @param rb RigidBody
         * @param fg Force generator
         */
        void remove(std::shared_ptr<RigidBody> rb, std::shared_ptr<ForceGenerator> fg);

        /**
         * @brief Clear the whole registry
         */
        void clear();

        /**
         * @brief Apply the force to the matching RigidBody
         * @param duration duration of the frame
         */
        void updateForces(float duration);

    private:
        Registry registry;
    };

    /**
     * @brief Gravity force generator for a RigidBody
     */
    class Gravity : public ForceGenerator
    {
    public:
        Gravity() = default;
        ~Gravity() override = default;

        /**
         * @brief Apply gravity to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(const std::shared_ptr<RigidBody>& rb, [[maybe_unused]] float duration) const override
        {
            rb->applyForce(Vector3{0.f, GRAVITY * PIXELS_PER_METER, 0.f});
        }
    };

    /**
     * @brief Static friction force generator for a RigidBody
     */
    class StaticFriction : public ForceGenerator
    {
    public:
        explicit StaticFriction(float coefficient) : coefficient(coefficient) {}
        ~StaticFriction() override = default;

        /**
         * @brief Apply static friction to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(const std::shared_ptr<RigidBody>& rb, [[maybe_unused]] float duration) const override
        {
            if (rb->isStatic())
                return;

            if (rb->velocity.norm() > EPSILON)
                return; // Movement, no static friction

            // Normal force magnitude is the weight of the body
            const float gravityMagnitude = GRAVITY * PIXELS_PER_METER;
            const float normalForceMagnitude = rb->getMass() * gravityMagnitude;

            const float maxStaticFriction = coefficient * normalForceMagnitude;

            // Get the sum of all forces applied to the body (except friction)
            const Vector3 appliedForce = rb->accumulatedForce;

            // Calculate the magnitude of the applied force
            float appliedForceMagnitude = appliedForce.norm();

            if (appliedForceMagnitude < maxStaticFriction)
            {
                // Apply static friction force, which is equal and opposite to the applied force
                Vector3 frictionForce = -appliedForce;
                rb->applyForce(frictionForce);
            }
        }

    private:
        float coefficient; // Coefficient of static friction
    };

    /**
     * @brief Kinetic friction force generator for a RigidBody
     */
    class KineticFriction : public ForceGenerator
    {
    public:
        explicit KineticFriction(float coefficient) : coefficient(coefficient) {}
        ~KineticFriction() override = default;

        /**
         * @brief Apply kinetic friction to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(const std::shared_ptr<RigidBody>& rb, [[maybe_unused]] float duration) const override
        {
            if (rb->isStatic())
                return;

            if (rb->velocity.norm() < EPSILON)
                return; // No movement, no kinetic friction

            // Normal force magnitude is the weight of the body
            const float gravityMagnitude = GRAVITY * PIXELS_PER_METER;
            const float normalForceMagnitude = rb->getMass() * gravityMagnitude;

            // Friction force: direction is opposite to velocity, magnitude is mu_k * |n|
            const Vector3 frictionDirection = -rb->velocity.normalized();
            const Vector3 frictionForce = frictionDirection * coefficient * normalForceMagnitude;

            rb->applyForce(frictionForce);
        }

    private:
        float coefficient; // Coefficient of kinetic friction
    };
}