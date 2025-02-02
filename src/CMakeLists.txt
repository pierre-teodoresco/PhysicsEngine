include(AddSFML)

add_library(engine engine/engine.cpp vector3/vector3.cpp particle/particle.cpp)
target_link_libraries(engine PRIVATE SFML::Graphics)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
