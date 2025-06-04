#include "RigidBody.hpp"
#include "Collider.hpp"
#include "PhysicsConstants.hpp"

namespace pe
{
    RigidBody::RigidBody(const Vector3& position, const Vector3& velocity, const Vector3& acceleration, float mass)
        : position(position),
          velocity(velocity),
          acceleration(acceleration),
          inverseMass(1.0f / mass) {};

    void RigidBody::applyForce(const Vector3 &force)
    {
        accumulatedForce += force;
    }

    float RigidBody::getMass() const
    {
        return 1.0f / inverseMass;
    }

    bool RigidBody::isStatic() const
    {
        return std::fabs(inverseMass) < EPSILON;
    }

    void RigidBody::makeStatic()
    {
        inverseMass = 0.f;
        acceleration = Vector3::zero();
        velocity = Vector3::zero();
    }

    void RigidBody::setCollider(std::unique_ptr<Collider> c)
    {
        this->collider = std::move(c);
    }

    void RigidBody::setRenderer(std::unique_ptr<Renderer> r)
    {
        this->renderer = std::move(r);
    }
}