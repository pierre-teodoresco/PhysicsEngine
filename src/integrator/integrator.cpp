#include "integrator.h"

namespace pe
{
    void Euler::integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration)
    {
        // Update velocity using acceleration
        velocity += acceleration * dt;

        // Update position using velocity
        position += velocity * dt + acceleration * 0.5f * dt * dt;
    }

    void Verlet::integrate(float dt, Vector3 &position, Vector3 &velocity, Vector3 &acceleration)
    {
        if (firstFrame)
        {
            // If it's the first frame, we need to initialize the previous position
            oldPosition = position - velocity * dt;
            firstFrame = false;
        }

        Vector3 temp = position;

        // Update position using old position and acceleration
        position = position * 2.0f - oldPosition + acceleration * dt * dt;

        // Update velocity using new position
        velocity = (position - oldPosition) / (2.0f * dt);

        oldPosition = temp;
    }
}