#include <memory>
#include <vector>
#include "RigidBody.hpp"

namespace pe
{
    /**
     * @brief Interface of a force for a RigidBody
     */
    class RigidBodyForceGenerator
    {
    public:
        RigidBodyForceGenerator() = default;
        virtual ~RigidBodyForceGenerator() = default;

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
    class RigidBodyForceRegistry
    {
    public:
        struct RigidBodyForceRegistration
        {
            std::shared_ptr<RigidBody> rb;
            std::shared_ptr<RigidBodyForceGenerator> fg;
        };

        typedef std::vector<RigidBodyForceRegistration> Registry;

        /**
         * @brief Add a RigidBody and its force generator to the registry
         * @param rb RigidBody
         * @param fg Force generator
         */
        void add(std::shared_ptr<RigidBody> rb, std::shared_ptr<RigidBodyForceGenerator> fg);

        /**
         * @brief Remove a RigidBody and its force generator from the registry
         * @param rb RigidBody
         * @param fg Force generator
         */
        void remove(std::shared_ptr<RigidBody> rb, std::shared_ptr<RigidBodyForceGenerator> fg);

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
    class RigidBodyGravity : public RigidBodyForceGenerator
    {
    public:
        RigidBodyGravity() = default;
        ~RigidBodyGravity() = default;

        /**
         * @brief Apply gravity to a RigidBody
         * @param rb targeted RigidBody
         * @param duration duration of a frame (unused)
         */
        void updateForce(std::shared_ptr<RigidBody> rb, [[maybe_unused]] float duration)
        {
            rb->applyForce(gravity);
        }

    private:
        Vector3 gravity{0.f, 9.81f, 0.f};
    };
}