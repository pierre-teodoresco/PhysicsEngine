#include "SphereCollider.hpp"
#include "BoxCollider.hpp"
#include "maths/Vector3.hpp"
#include "RigidBody.hpp"
#include <algorithm>

namespace pe
{
    ContactManifold SphereCollider::isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const
    {
        // Use double dispatch to call the specific collision method
        return other.isCollidingWithSphere(*this, otherBody, self);
        // Note : we pass `otherBody` as the first argument because `self` is the one that owns this collider, and `otherBody` is the one that owns the other collider.
    }

    ContactManifold SphereCollider::isCollidingWithSphere(const SphereCollider &sphere, const RigidBody &self, const RigidBody &otherBody) const
    {
        ContactManifold result;

        // Vector from sphere center to other sphere center
        Vector3 delta = self.position - otherBody.position;

        // Check if the spheres are colliding
        if (const float dist = delta.norm(); dist <= (this->radius + sphere.radius))
        {
            result.colliding = true;
            // Normal from sphere to sphere
            result.normal = delta.normalized();
            result.penetration = (this->radius + sphere.radius) - dist;
            // Contact point is the point on the surface of this sphere in the direction of the normal
            result.contactPoint = self.position + (result.normal * this->radius);
            result.restitution = std::max(restitution, sphere.restitution); // Use the maximum restitution of both colliders
        }
        else
        {
            result.colliding = false;
        }

        return result;
    }

    // Sphere vs Box (AABB)
    ContactManifold SphereCollider::isCollidingWithBox(const BoxCollider &box, const RigidBody &self, const RigidBody &otherBody) const
    {
        ContactManifold result;

        // Calculate the closest point on the box to the sphere center
        const auto minBox = otherBody.position;
        const auto maxBox = otherBody.position + Vector3(box.length, box.width, box.height);

        const float closestPointX = std::max(minBox.getX(), std::min(self.position.getX(), maxBox.getX()));
        const float closestPointY = std::max(minBox.getY(), std::min(self.position.getY(), maxBox.getY()));
        const float closestPointZ = std::max(minBox.getZ(), std::min(self.position.getZ(), maxBox.getZ()));
        const Vector3 closestPoint(closestPointX, closestPointY, closestPointZ);

        // Vector from closest point to sphere center
        const Vector3 delta = self.position - closestPoint;


        if (const float dist = delta.norm(); dist <= radius)
        {
            result.colliding = true;
            result.normal = delta.normalized();
            result.penetration = radius - dist;
            result.contactPoint = closestPoint + result.normal * radius;
            result.restitution = std::max(restitution, box.restitution);
        }
        else
        {
            result.colliding = false;
        }

        return result;
    }

    // DEBUG: Draw the sphere collider
    void SphereCollider::draw(sf::RenderWindow &window, const pe::RigidBody &body) const
    {
        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2.f);
        shape.setOrigin(sf::Vector2f(radius, radius)); // Set origin to center of circle
        shape.setPosition(sf::Vector2f(body.position.getX(), body.position.getY()));
        window.draw(shape);
    }
}
