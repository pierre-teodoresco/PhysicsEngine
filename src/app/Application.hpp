#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "scenes/Scene.hpp"
#include "scenes/BalisticScene.hpp"
#include "scenes/BalldropScene.hpp"
/**
 * @brief The main application class
 */
class Application
{
public:
    Application() : window(sf::VideoMode({WIDTH, HEIGHT}), TITLE), scene{std::make_unique<Balldrop>()} {}
    ~Application() = default;

    /**
     * @brief Run the application
     */
    void run();

    static constexpr auto TITLE{"Physics Engine - Balistic"};
    static constexpr auto WIDTH{1000u};
    static constexpr auto HEIGHT{800u};
    static constexpr auto UPS{144u}; // Update Per Second

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

    // Scene
    std::unique_ptr<Scene> scene;
};
