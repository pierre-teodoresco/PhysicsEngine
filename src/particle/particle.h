#pragma once

#include "vector3/vector3.h"
#include <SFML/Graphics.hpp>

/**
 * @brief The particle class
 */
class Particle
{
public:
    enum class Integrator
    {
        Euler,
        Verlet
    };

    Particle() = default;

    Particle(Vector3 position, Vector3 velocity , Vector3 acceleration , float mass, float damping, Integrator integrator)
        : position(position),
        velocity(velocity),
        acceleration(acceleration),
        inverseMass(1.0f / mass),
        damping(damping),
        integrator(integrator) {};

    ~Particle() = default;

    /**
     * @brief Compute the force applied to the particle
     * @param force The force applied to the particle
     */
    void addForce(const Vector3 &force);

    /**
     * @brief Update the particle's velocity and position
     * @param dt The time step (frame time)
     */
    void integrate(float dt);

    /**
     * @brief Render the particle
     */
    void render(sf::RenderWindow &window) const;

    /**
     * @brief Get the position of the particle
     * @return The position of the particle
     */
    [[nodiscard]] Vector3 getPosition() const;

    /**
     * @brief Get the velocity of the particle
     * @return The velocity of the particle
     */
    [[nodiscard]] Vector3 getVelocity() const;

    /**
     * @brief Get the acceleration of the particle
     * @return The acceleration of the particle
     */
    [[nodiscard]] Vector3 getAcceleration() const;

    /**
     * @brief Get the mass of the particle
     * @return The mass of the particle
     */
    [[nodiscard]] float getMass() const;

    /**
     * @brief Choose integration method
     * @param integration The integration method
     */
    void setIntegration(Integrator i);

    /**
     * @brief Set the mass of the particle
     * @param mass The mass of the particle
     */
    void setMass(float mass);

    /**
     * @brief Set the damping of the particle. The damping factor represents the percentage of velocity kept after each frame
     * @param damping The damping of the particle
     */
    void setDamping(float damping);

    static constexpr float RADIUS = 50.f;

private:
    Vector3 position{};
    Vector3 oldPosition{};
    Vector3 velocity{};
    Vector3 acceleration{};

    float inverseMass{1.f};
    float damping{.8f};
    Integrator integrator{Integrator::Euler};
    bool firstFrame {true};

    /**
     * @brief Euler integration
     * @param dt The time step (frame time)
     */
    void euler(float dt);

    /**
     * @brief Verlet integration
     * @param dt The time step (frame time)
     */
    void verlet(float dt);
};