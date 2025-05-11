# PhysicsEngine

## Auteur
- Pierre Teodoresco - 3A SN

## Introduction

Ce projet est un moteur physique simple développé en C++ dans le cadre d'un TP. Il vise à illustrer les concepts fondamentaux de la simulation physique, tels que la gestion des particules, l'application des forces et l'intégration numérique. La bibliothèque [SFML](https://www.sfml-dev.org/) est utilisée pour la création de la fenêtre, la gestion des événements et le rendu graphique 2D simple.

## Fonctionnalités Actuelles

L'application actuelle est une démonstration de simulation balistique en 2D :
-   L'utilisateur peut cliquer dans la fenêtre.
-   Un clic crée une particule au coin inférieur gauche de l'écran.
-   La vitesse initiale de la particule est déterminée par la direction entre le point de départ et la position du clic.
-   Les particules suivent une trajectoire parabolique sous l'effet de la gravité.
-   Les particules disparaissent lorsqu'elles sortent des limites de la fenêtre.

## Architecture

Le projet est structuré de manière modulaire pour faciliter la compréhension et l'extension :

-   `Vector3` (`src/vector3/`): Implémente une classe pour la manipulation de vecteurs 3D (positions, vitesses, accélérations, forces), avec les opérations vectorielles de base.
-   `Particle` (`src/particle/`): Représente une particule physique. Elle contient son état (position, vitesse, accélération, masse) et gère l'accumulation des forces ainsi que la mise à jour de son état via un intégrateur.
-   `Integrator` (`src/integrator/`): Définit une interface (`Integrator`) pour les algorithmes d'intégration numérique, qui calculent l'évolution de l'état d'une particule au cours du temps. Des implémentations concrètes (`Euler`, `Verlet`) sont fournies.
-   `Game` (`src/game/`): Définit une interface abstraite (`Game`) pour une simulation spécifique. Elle contient la logique de la simulation (mise à jour des objets, gestion des interactions). La classe `Balistic` est une implémentation concrète de cette interface pour la démo actuelle.
-   `Application` (`src/application/`): Gère la boucle principale de l'application, la fenêtre SFML, les événements utilisateur (clavier, souris), et orchestre les appels aux méthodes `update` et `render` de l'objet `Game` courant.
-   `main.cpp`: Point d'entrée de l'application, crée et lance l'objet `Application`.
-   `test/`: Contient les tests unitaires (actuellement pour la classe `Vector3`).

## Concepts Clés

### Particules (`Particle`)
La classe `Particle` est au cœur de la simulation. Chaque instance représente un objet ponctuel avec :
-   Une **position**, une **vitesse** et une **accélération** (vecteurs 3D).
-   Une **masse** (stockée en interne comme une masse inverse, `inverseMass`, pour simplifier les calculs et gérer les masses infinies/nulles).
-   Une méthode `addForce(force)` pour accumuler les forces externes appliquées à la particule à chaque pas de temps. L'accélération résultante est calculée en utilisant F=ma (ou a = F * inverseMass).
-   Une méthode `integrate(dt)` qui délègue la mise à jour de la position et de la vitesse à un objet `Integrator`, en fonction de l'accélération accumulée et du pas de temps `dt`.

### Intégration Numérique (`Integrator`)
L'intégration numérique est le processus qui permet de calculer l'état futur (position, vitesse) d'une particule à partir de son état actuel et des forces qui lui sont appliquées. Le moteur fournit une interface `Integrator` et deux implémentations :
-   **Euler:** Un intégrateur simple mais potentiellement moins stable et précis.
-   **Verlet:** Un intégrateur plus stable, particulièrement adapté pour la physique des jeux. Il utilise la position actuelle et précédente pour calculer la nouvelle position.

Chaque `Particle` possède un pointeur vers un `Integrator` (par défaut `Verlet` dans la démo `Balistic`) qui est utilisé lors de l'appel à `integrate(dt)`.

### Boucle de Jeu (`Application::run`)
L'`Application` utilise une boucle de jeu à pas de temps fixe :
1.  Calcule le temps écoulé depuis la dernière frame.
2.  Exécute la logique de mise à jour (`update`) un nombre fixe de fois par seconde (`UPS`), indépendamment de la fréquence de rafraîchissement de l'écran. Cela garantit une simulation physique déterministe et stable. La méthode `update` de l'`Application` appelle la méthode `update` du `Game` actif (ici, `Balistic`).
3.  Gère les événements SFML (fermeture de fenêtre, entrées utilisateur).
4.  Effectue le rendu (`render`) aussi souvent que possible. La méthode `render` de l'`Application` appelle la méthode `render` du `Game` actif.

### Simulations (`Game`)
L'interface `Game` permet de découpler la logique spécifique d'une simulation (comme `Balistic`) de la structure générale de l'application. Pour créer une nouvelle simulation, il suffit de créer une classe héritant de `Game` et d'implémenter les méthodes virtuelles pures `update(window, dt)` et `render(window)`.

## Prérequis

Pour compiler et exécuter ce projet, vous aurez besoin de :
-   Un compilateur C++ supportant C++17 (ou supérieur).
-   CMake (version 3.10 ou supérieur).
-   La bibliothèque SFML (version 2.5 ou supérieur). Assurez-vous qu'elle est correctement installée et accessible par CMake.

## Compilation et Exécution

### Compiler le Projet
Utilisez les commandes CMake suivantes depuis la racine du projet :
```bash
cmake -S . -B build
cmake --build build --target physics_engine
./build/bin/physics_engine
```

### Lancer les Tests Unitaires
```bash
cmake -S . -B build
cmake --build build --target test_vector3
./build/bin/test_vector3
```

## Comment Utiliser

Ce projet sert de base pour explorer la simulation physique. Voici quelques pistes :

1.  **Créer une nouvelle Simulation:**
    *   Créez une nouvelle classe héritant de `Game`.
    *   Implémentez les méthodes `update` et `render` pour votre simulation.
    *   Modifiez `src/application/application.h` pour instancier votre nouvelle classe `Game` à la place de `Balistic`.
2.  **Gérer les Particules:**
    *   Instanciez des objets `Particle` dans votre classe `Game`.
    *   Définissez leurs propriétés initiales (position, vitesse, masse).
    *   Appelez `particle.integrate(dt)` dans la méthode `update` de votre `Game`.
    *   Appelez `particle.render(window)` dans la méthode `render` de votre `Game`.
3.  **Appliquer des Forces:**
    *   Dans la méthode `update` de votre `Game`, calculez les forces agissant sur chaque particule (gravité, ressorts, forces utilisateur, etc.).
    *   Utilisez `particle.addForce(calculated_force)` pour appliquer chaque force. L'accélération de la particule est réinitialisée à zéro au début de chaque appel à `integrate`, donc les forces doivent être ajoutées à chaque pas de temps.
4.  **Choisir un Intégrateur:**
    *   Vous pouvez spécifier l'intégrateur lors de la création d'une `Particle` ou via `particle.setIntegrator(std::make_shared<Euler>())`. Expérimentez avec `Euler` et `Verlet` pour observer les différences.

## Structure du Code

```
.
├── CMakeLists.txt          # Fichier CMake principal
├── README.md               # Cette documentation
├── main.cpp                # Point d'entrée
├── src/                    # Code source du moteur et de la démo
│   ├── CMakeLists.txt      # CMake pour le répertoire src
│   ├── application/        # Gestion de l'application SFML
│   ├── game/               # Logique des simulations (Game, Balistic)
│   ├── integrator/         # Algorithmes d'intégration (Integrator, Euler, Verlet)
│   ├── particle/           # Classe Particle
│   └── vector3/            # Classe Vector3
├── test/                   # Tests unitaires
│   ├── CMakeLists.txt      # CMake pour les tests
│   └── test_vector3.cpp    # Tests pour Vector3
└── ...                     # Autres fichiers (build, cmake, .git, etc.)
```