#pragma once

#include "vector3/vector3.h"
#include "integrator/integrator.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

/**
 * @brief The particle class
 */
class Particle
{
public:
    /**
     * @brief Create a new particle
     * @param position initial position of the particle (default to origin)
     * @param velocity initial velocity of the particle (default to zero)
     * @param acceleration initial acceleration of the particle (default to zero)
     * @param mass mass of the particle (default to 1.0f)
     * @param integrator integration method (default to Verlet)
     */
    Particle(
        Vector3 position = Vector3::zero(),
        Vector3 velocity = Vector3::zero(),
        Vector3 acceleration = Vector3::zero(),
        float mass = 1.0f,
        std::shared_ptr<Integrator> integrator = std::make_shared<Verlet>());
    ~Particle();

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
    Vector3 getPosition() const;

    /**
     * @brief Get the velocity of the particle
     * @return The velocity of the particle
     */
    Vector3 getVelocity() const;

    /**
     * @brief Get the acceleration of the particle
     * @return The acceleration of the particle
     */
    Vector3 getAcceleration() const;

    /**
     * @brief Get the mass of the particle
     * @return The mass of the particle
     */
    float getMass() const;

    /**
     * @brief Choose integration method
     * @param integration The integration method
     */
    void setIntegrator(std::shared_ptr<Integrator> integrator);

    /**
     * @brief Set the mass of the particle
     * @param mass The mass of the particle
     */
    void setMass(float mass);

    static constexpr float RADIUS = 50.f;

private:
    Vector3 position, velocity, acceleration;
    float inverseMass;
    std::shared_ptr<Integrator> integrator;
};