#include <memory>
#include <vector>
#include "particle/particle.h"

namespace pe
{
    /**
     * @brief Interface of a force for a particle
     */
    class ParticleForceGenerator
    {
    public:
        ParticleForceGenerator() = default;
        virtual ~ParticleForceGenerator() = default;

        /**
         * @brief Apply a force to a particle
         * @param particle particle on which the force is applied
         * @param duration duration of the frame
         */
        virtual void updateForce(std::shared_ptr<Particle> particle, float duration) = 0;
    };

    /**
     * @brief Manage which force is apply to which particle of the system
     */
    class ParticleForceRegistry
    {
    public:
        struct ParticleForceRegistration
        {
            std::shared_ptr<Particle> particle;
            std::shared_ptr<ParticleForceGenerator> fg;
        };

        typedef std::vector<ParticleForceRegistration> Registry;

        /**
         * @brief Add a particle and its force generator to the registry
         * @param particle
         * @param fg Force generator
         */
        void add(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> fg);

        /**
         * @brief Remove a particle and its force generator from the registry
         * @param particle
         * @param fg Force generator
         */
        void remove(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> fg);

        /**
         * @brief Clear the whole registry
         */
        void clear();

        /**
         * @brief Apply the force to the matching particle
         * @param duration duration of the frame
         */
        void updateForces(float duration);

    private:
        Registry registry;
    };

    /**
     * @brief Gravity force generator for a particle
     */
    class ParticleGravity : public ParticleForceGenerator
    {
    public:
        ParticleGravity() = default;
        ~ParticleGravity() = default;

        /**
         * @brief Apply gravity to a particle
         * @param particle targeted particle
         * @param duration duration of a frame (unused)
         */
        void updateForce(std::shared_ptr<Particle> particle, [[maybe_unused]] float duration)
        {
            particle->addForce(gravity);
        }

    private:
        Vector3 gravity{0.f, 9.81f, 0.f};
    };
}