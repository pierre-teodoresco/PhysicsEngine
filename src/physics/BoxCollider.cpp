#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "maths/Vector3.hpp"
#include "RigidBody.hpp"

namespace pe
{
    ContactManifold BoxCollider::isColliding(const Collider &other, const RigidBody &self, const RigidBody &otherBody) const
    {
        // Use double dispatch to call the specific collision method
        return other.isCollidingWithBox(*this, otherBody, self);
        // Note: we swap self/otherBody to match the correct ownership
    }

    ContactManifold BoxCollider::isCollidingWithSphere(const SphereCollider &sphere, const RigidBody &self, const RigidBody &otherBody) const
    {
        // Use the SphereCollider's method to check collision with a box
        // Note: we swap self/otherBody to match the correct ownership
        return sphere.isCollidingWithBox(*this, otherBody, self);
    }

    ContactManifold BoxCollider::isCollidingWithBox(const BoxCollider &box, const RigidBody &self, const RigidBody &otherBody) const
    {
        ContactManifold result;

        // Compute min/max corners for both boxes (A and B)
        Vector3 minA = self.position - Vector3(length / 2, width / 2, height / 2);
        Vector3 maxA = self.position + Vector3(length / 2, width / 2, height / 2);
        Vector3 minB = otherBody.position - Vector3(box.length / 2, box.width / 2, box.height / 2);
        Vector3 maxB = otherBody.position + Vector3(box.length / 2, box.width / 2, box.height / 2);

        // Check for overlap on all axes
        bool overlapX = (minA.getX() <= maxB.getX() && maxA.getX() >= minB.getX());
        bool overlapY = (minA.getY() <= maxB.getY() && maxA.getY() >= minB.getY());
        bool overlapZ = (minA.getZ() <= maxB.getZ() && maxA.getZ() >= minB.getZ());

        if (overlapX && overlapY && overlapZ)
        {
            result.colliding = true;

            // Calculate penetration depth and collision normal (for AABBs)
            // Find the axis of minimum penetration
            float penX = std::min(maxA.getX(), maxB.getX()) - std::max(minA.getX(), minB.getX());
            float penY = std::min(maxA.getY(), maxB.getY()) - std::max(minA.getY(), minB.getY());
            float penZ = std::min(maxA.getZ(), maxB.getZ()) - std::max(minA.getZ(), minB.getZ());

            // Find the axis with the smallest penetration
            float minPenetration = penX;
            Vector3 normal(1, 0, 0);
            if (penY < minPenetration)
            {
                minPenetration = penY;
                normal = Vector3(0, 1, 0);
            }
            if (penZ < minPenetration)
            {
                minPenetration = penZ;
                normal = Vector3(0, 0, 1);
            }

            // Determine the direction of the normal (from A to B)
            Vector3 centerA = self.position;
            Vector3 centerB = otherBody.position;
            Vector3 dir = centerB - centerA;
            if (normal.dot(dir) < 0)
                normal = -normal;

            result.normal = normal;
            result.penetration = minPenetration;

            // Contact point: center of the overlapping region (approximation)
            float contactX = std::max(minA.getX(), minB.getX()) + penX * 0.5f;
            float contactY = std::max(minA.getY(), minB.getY()) + penY * 0.5f;
            float contactZ = std::max(minA.getZ(), minB.getZ()) + penZ * 0.5f;
            result.contactPoint = Vector3(contactX, contactY, contactZ);

            // Set restitution based on the box with the higher restitution value
            result.restitution = std::max(restitution, box.restitution);
        }
        else
        {
            result.colliding = false;
        }

        return result;
    }

    // DEBUG: Draw the sphere collider
    void BoxCollider::draw(sf::RenderWindow &window, const pe::RigidBody &body) const
    {
        sf::RectangleShape shape(sf::Vector2f(length, width));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2.f);
        shape.setPosition(sf::Vector2f(body.position.getX(), body.position.getY()));
        window.draw(shape);
    }
}