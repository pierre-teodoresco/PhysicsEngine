#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "game/game.h"
#include "game/balistic.h"

/**
 * @brief The main application class
 */
class Application
{
public:
    Application();

    /**
     * @brief Run the application
     */
    void run();

    static constexpr auto TITLE = "Physics Engine - Demo";
    static constexpr auto WIDTH = 1920u;
    static constexpr auto HEIGHT = 1080u;
    static constexpr auto FPS = 60u;

private:
    /**
     * @brief Handle events
     */
    void handleEvents();

    /**
     * @brief Render the window
     */
    void render();

    /**
     * @brief Update the window
     * @param dt Delta time
     */
    void update(float dt);

    sf::RenderWindow window;

    // Game
    std::shared_ptr<Game> game;
};
