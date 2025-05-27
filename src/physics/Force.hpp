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
        virtual void updateForce(std::shared_ptr<RigidBody> rb, float duration) = 0;
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

        typedef std::vector<ForceRegistration> Registry;

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
        ~Gravity() = default;

        /**
         * @brief Apply gravity to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(std::shared_ptr<RigidBody> rb, [[maybe_unused]] float duration)
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
        StaticFriction(float coefficient) : coefficient(coefficient) {}
        ~StaticFriction() = default;

        /**
         * @brief Apply static friction to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(std::shared_ptr<RigidBody> rb, [[maybe_unused]] float duration) override
        {
            if (rb->isStatic())
                return;

            if (rb->velocity.norm() > EPSILON)
                return; // Movement, no static friction

            // Normal force magnitude is the weight of the body
            float gravityMagnitude = GRAVITY * PIXELS_PER_METER;
            float normalForceMagnitude = rb->getMass() * gravityMagnitude;

            float maxStaticFriction = coefficient * normalForceMagnitude;

            // Get the sum of all forces applied to the body (except friction)
            Vector3 appliedForce = rb->accumulatedForce;

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
        KineticFriction(float coefficient) : coefficient(coefficient) {}
        ~KineticFriction() = default;

        /**
         * @brief Apply kinetic friction to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(std::shared_ptr<RigidBody> rb, [[maybe_unused]] float duration) override
        {
            if (rb->isStatic())
                return;

            if (rb->velocity.norm() < EPSILON)
                return; // No movement, no kinetic friction

            // Normal force magnitude is the weight of the body
            float gravityMagnitude = GRAVITY * PIXELS_PER_METER;
            float normalForceMagnitude = rb->getMass() * gravityMagnitude;

            // Friction force: direction is opposite to velocity, magnitude is mu_k * |n|
            Vector3 frictionDirection = -rb->velocity.normalized();
            Vector3 frictionForce = frictionDirection * coefficient * normalForceMagnitude;

            rb->applyForce(frictionForce);
        }

    private:
        float coefficient; // Coefficient of kinetic friction
    };
}