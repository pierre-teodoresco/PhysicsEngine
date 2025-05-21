#include "Force.hpp"

namespace pe
{
    void RigidBodyForceRegistry::add(std::shared_ptr<RigidBody> rb, std::shared_ptr<RigidBodyForceGenerator> fg)
    {
        registry.push_back({rb, fg});
    }

    void RigidBodyForceRegistry::remove(std::shared_ptr<RigidBody> rb, std::shared_ptr<RigidBodyForceGenerator> fg)
    {
        registry.erase(
            std::remove_if(
                registry.begin(),
                registry.end(),
                [&](const RigidBodyForceRegistration &registration)
                {
                    return registration.rb == rb && registration.fg == fg;
                }),
            registry.end());
    }

    void RigidBodyForceRegistry::clear()
    {
        registry.clear();
    }

    void RigidBodyForceRegistry::updateForces(float duration)
    {
        for (auto entry : registry)
        {
            entry.fg->updateForce(entry.rb, duration);
        }
    }
}