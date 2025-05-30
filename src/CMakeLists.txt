include(AddSFML)

# Crée une bibliothèque pour le moteur (core, physics, maths)
add_library(engine
    maths/Vector3.cpp
    physics/Force.cpp
    physics/RigidBody.cpp
    physics/BoxCollider.cpp
    physics/SphereCollider.cpp
)
target_link_libraries(engine PRIVATE SFML::Graphics)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(engine PRIVATE ${MY_COMPILE_OPTIONS})

# Crée une bibliothèque pour la scène de démo
add_library(scene
    scenes/BalisticScene.cpp
    scenes/BalldropScene.cpp
)
target_link_libraries(scene PRIVATE SFML::Graphics engine)

# Crée une bibliothèque d'application (boucle principale)
add_library(application
    app/Application.cpp
)
target_link_libraries(application PRIVATE SFML::Graphics engine scene)
target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(application PRIVATE ${MY_COMPILE_OPTIONS})