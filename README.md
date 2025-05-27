# PhysicsEngine

## Auteur
- Pierre Teodoresco - 3A SN

## Introduction

Ce projet est un moteur physique 2D développé en C++ dans le cadre d'un TP. Il implémente une simulation physique avec gestion des collisions, des forces et de l'intégration numérique. La bibliothèque [SFML](https://www.sfml-dev.org/) est utilisée pour le rendu graphique et la gestion des événements.

## Fonctionnalités

L'application actuelle est une démonstration de chûtes de balles avec collisions :
- L'utilisateur peut cliquer dans la fenêtre
- Un clic crée une balle à l'emplacement du clic
- Les balles tombent sous l'effet de la gravité
- Les balles rebondissent entre elles de manière élastique
- Les balles rebondissent sur un sol fixe
- Les balles disparaissent lorsqu'elles sortent des limites de la fenêtre
- Les bords rouges représentent les colliders
- Les points rouge représentent la position des corps rigides

Il y a aussi une démonstration de tir balistique :
- L'utilisateur peut cliquer dans la fenêtre
- Un clic crée un projectile au coin inférieur gauche de l'écran
- La vitesse initiale du projectile est déterminée par la direction entre le point de départ et la position du clic
- Les projectiles suivent une trajectoire parabolique sous l'effet de la gravité
- Les projectiles entrent en collision entre elles de manière élastique
- Les projectiles disparaissent lorsqu'ils sortent des limites de la fenêtre

## Architecture

Le projet est structuré de manière modulaire :

- `physics/` : Composants fondamentaux du moteur physique
  - `PhysicsContants` : Regroupe un ensemble de constantes physiques
  - `RigidBody` : Représente un corps rigide avec position, vitesse, accélération et masse
  - `Force` : Gestion des forces (gravité, frictions, registre de forces)
  - `Integrator` : Algorithmes d'intégration numérique (Euler, Verlet)
  - `Collider` : Interface pour les formes de collision
  - `SphereCollider` : Implémentation de collision pour les sphères
  - `BoxCollider` : Implémentation de collision pour les parallélépipèdes rectangles
  - `CollisionManager` : Gestion des collisions entre corps rigides

- `maths/` : Utilitaires mathématiques
  - `Vector3` : Classe pour la manipulation de vecteurs 3D

- `graphics/` : Système de rendu
  - `Renderer` : Interface pour le rendu des corps
  - `CircleRenderer` : Rendu 2D des corps circulaires
  - `BoxRenderer` : Rendu 2D des corps rectangulaires

- `scenes/` : Scènes de démonstration
  - `Scene` : Interface pour les scènes
  - `BalisticScene` : Démo de trajectoire balistique
  - `BalldropScene` : Démo de chute de balles

- `app/` : Gestion de l'application
  - `Application` : Boucle principale, gestion de la fenêtre SFML

## Prérequis

- Compilateur C++17 ou supérieur
- CMake 3.10 ou supérieur
- SFML 3.0.1 ou supérieur

## Compilation

```bash
cmake -S . -B build
cmake --build build --target physics_engine
./build/bin/physics_engine
```

## Structure du Code

```
.
├── CMakeLists.txt          # Configuration CMake principale
├── README.md               # Documentation
├── main.cpp                # Point d'entrée
├── src/                    # Code source
│   ├── CMakeLists.txt      # Configuration CMake pour src
│   ├── app/                # Gestion de l'application
│   ├── physics/            # Composants physiques
│   ├── graphics/           # Système de rendu
│   ├── maths/              # Utilitaires mathématiques
│   └── scenes/             # Scènes de démonstration
└── test/                   # Tests unitaires
```

## Comment Utiliser

1. **Créer une nouvelle Scène**
   - Créez une classe héritant de `Scene`
   - Implémentez `update` et `render`
   - Modifiez `Application.hpp` pour utiliser votre scène (constructeur de `Application`)

2. **Gérer les Corps Rigides**
   - Créez des `RigidBody` avec position, vitesse et masse
   - Ajoutez des colliders (ex: `SphereCollider`)
   - Ajoutez des renderers (ex: `CircleRenderer`)

3. **Appliquer des Forces**
   - Utilisez `ForceRegistry` pour gérer les forces
   - Créez des générateurs de force héritant de `ForceGenerator`
   - Appliquez les forces via `applyForce`

4. **Choisir un Intégrateur**
   - Utilisez `EulerIntegrator` ou `VerletIntegrator`
   - L'intégrateur gère la mise à jour de la position et de la vitesse