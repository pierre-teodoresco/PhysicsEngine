include(AddSFML)

add_library(application application/application.cpp game/balistic.cpp vector3/vector3.cpp particle/particle.cpp)
target_link_libraries(application PRIVATE SFML::Graphics)
target_include_directories(application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
