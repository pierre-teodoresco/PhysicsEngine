#include "Force.hpp"

namespace pe
{
    void ForceRegistry::add(std::shared_ptr<RigidBody> rb, std::shared_ptr<ForceGenerator> fg)
    {
        registry.push_back({rb, fg});
    }

    void ForceRegistry::remove(std::shared_ptr<RigidBody> rb, std::shared_ptr<ForceGenerator> fg)
    {
        registry.erase(
            std::remove_if(
                registry.begin(),
                registry.end(),
                [&](const ForceRegistration &registration)
                {
                    return registration.rb == rb && registration.fg == fg;
                }),
            registry.end());
    }

    void ForceRegistry::clear()
    {
        registry.clear();
    }

    void ForceRegistry::updateForces(float duration)
    {
        for (auto entry : registry)
        {
            entry.fg->updateForce(entry.rb, duration);
        }
    }
}