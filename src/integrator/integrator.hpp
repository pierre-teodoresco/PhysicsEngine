#pragma once

#include "vector3/vector3.h"

class Integrator
{
public:
    Integrator() = default;
    virtual ~Integrator() = default;

    virtual void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) = 0;
};

class Euler : public Integrator
{
public:
    Euler() = default;
    ~Euler() = default;

    void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) override
    {
        // Update velocity using acceleration
        velocity += acceleration * dt;

        // Update position using velocity
        position += velocity * dt + acceleration * 0.5f * dt * dt;
    }
};

class Verlet : public Integrator
{
public:
    Verlet() = default;
    ~Verlet() = default;

    void integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration) override
    {
        if (firstFrame)
        {
            // If it's the first frame, we need to initialize the previous position
            oldPosition = position - velocity * dt;
        }

        Vector3 temp = position;

        // Update position using old position and acceleration
        position = position * 2.0f - oldPosition + acceleration * dt * dt;

        // Update velocity using new position
        velocity = (position - oldPosition) / (2.0f * dt);

        oldPosition = temp;
    }

private:
    Vector3 oldPosition;
    bool firstFrame = true;
};