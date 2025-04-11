#include "force.h"

namespace pe
{
    void ParticleForceRegistry::add(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> fg)
    {
        registry.push_back({particle, fg});
    }

    void ParticleForceRegistry::remove(std::shared_ptr<Particle> particle, std::shared_ptr<ParticleForceGenerator> fg)
    {
        registry.erase(
            std::remove_if(
                registry.begin(),
                registry.end(),
                [&](const ParticleForceRegistration &registration)
                {
                    return registration.particle == particle && registration.fg == fg;
                }),
            registry.end());
    }

    void ParticleForceRegistry::clear()
    {
        registry.clear();
    }

    void ParticleForceRegistry::updateForces(float duration)
    {
        for (auto entry : registry)
        {
            entry.fg->updateForce(entry.particle, duration);
        }
    }
}