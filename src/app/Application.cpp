#include "Application.hpp"

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / UPS);

    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate >= timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;

            handleEvents();
            update(timePerFrame.asSeconds());
        }

        render();
    }
}
void Application::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

void Application::render()
{
    window.clear(sf::Color::Black);

    // render the scene
    scene->render(window);

    window.display();
}

void Application::update(float dt)
{
    // update the scene
    scene->update(window, dt);
}