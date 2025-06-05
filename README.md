# PhysicsEngine

## Author
- Pierre Teodoresco - 3A SN

## Introduction

This project is a 2D physics engine developed in C++ as part of a lab assignment.
It implements a physics simulation with collision handling, forces, and numerical integration.
The [SFML](https://www.sfml-dev.org/) library is used for graphics rendering and event management.

## Features

The current application is a demonstration of ball drops with collisions:
- The user can click in the window
- A click creates a ball at the click location
- The ball falls under the effect of gravity
- Balls bounce off each other elastically
- Balls bounce on a fixed ground
- Balls disappear when they leave the window boundaries
- Red edges represent the colliders
- Red dots represent the position of the rigid bodies

There is also a demonstration of ballistic shooting:
- The user can click in the window
- A click creates a projectile in the bottom left corner of the screen
- The initial speed of the projectile is determined by the direction between the starting point and the click position
- Projectiles follow a parabolic trajectory under the effect of gravity
- Projectiles collide with each other elastically
- Projectiles disappear when they leave the window boundaries

## Architecture

The project is structured in a modular way:

- `physics/`: Core components of the physics engine
  - `PhysicsContants`: Groups a set of physical constants
  - `RigidBody`: Represents a rigid body with position, velocity, acceleration, and mass
  - `Force`: Manages forces (gravity, friction, force registry)
  - `Integrator`: Numerical integration algorithms (Euler, Verlet)
  - `Collider`: Interface for collision shapes
  - `SphereCollider`: Collision implementation for spheres
  - `BoxCollider`: Collision implementation for rectangular boxes
  - `CollisionManager`: Manages collisions between rigid bodies

- `maths/`: Mathematical utilities
  - `Vector3`: Class for manipulating 3D vectors

- `graphics/`: Rendering system
  - `Renderer`: Interface for rendering bodies
  - `CircleRenderer`: 2D rendering of circular bodies
  - `BoxRenderer`: 2D rendering of rectangular bodies

- `scenes/`: Demo scenes
  - `Scene`: Interface for scenes
  - `BalisticScene`: Ballistic trajectory demo
  - `BalldropScene`: Ball drop demo

- `app/`: Application management
  - `Application`: Main loop, SFML window management

## Requirements

- C++17 compiler or higher
- CMake 3.10 or higher
- SFML 3.0.1 or higher

## Compilation

```bash
cmake -S . -B build
cmake --build build --target physics_engine
./build/bin/physics_engine
## Structure du Code
```

## Project Structure
```
.
├── CMakeLists.txt          # Main CMake configuration
├── README.md               # Documentation
├── main.cpp                # Main application
├── src/                    # Source files
│   ├── CMakeLists.txt      # CMake configuration for src
│   ├── app/                # Application management
│   ├── physics/            # Physics engine core
│   ├── graphics/           # Rendering system
│   ├── maths/              # Mathematical utilities
│   └── scenes/             # Demo scenes
└── test/                   # Unit tests
    ├── CMakeLists.txt      # CMake configuration for tests
    └── ...                 # Test files
```

## How to Use
   
   1. **Create a New Scene**
      - Create a class inheriting from `Scene`
      - Implement `update` and `render`
      - Modify `Application.hpp` to use your scene (in the `Application` constructor)
   
   2. **Manage Rigid Bodies**
      - Create `RigidBody` objects with position, velocity, and mass
      - Add colliders (e.g., `SphereCollider`)
      - Add renderers (e.g., `CircleRenderer`)
   
   3. **Apply Forces**
      - Use `ForceRegistry` to manage forces
      - Create force generators inheriting from `ForceGenerator`
      - Apply forces via `applyForce`
   
   4. **Choose an Integrator**
      - Use `EulerIntegrator` or `VerletIntegrator`
      - The integrator handles updating position and velocity