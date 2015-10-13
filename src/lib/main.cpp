#include <SFML/Graphics.hpp>

#include "../include/tools.hpp"
#include "../include/Window.hpp"
#include "../include/Level.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/ResourceLoading.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/GameStateMenu.hpp"
#include "../include/TDoodad.hpp"

#include <iostream>

constexpr float MAXIMAL_FRAME_DURATION = 1/15.f;

int main()
{
	// Initializing window
	Window::Initialize();
    sf::RenderWindow& window = *(new sf::RenderWindow(Window::windowedVideoMode, GAME_TITLE, sf::Style::Titlebar | sf::Style::Close));
    resizeWindow(window, Window::windowedVideoMode.width, Window::windowedVideoMode.height);
    window.setFramerateLimit(300);
    // frame time counter
    sf::Clock clockwerk;
    // Initializing resources
	ResourceManager::Initialize();
	LoadResources();
	std::string sharePath("C:/Users/Teddy/Documents/GitHub/RusTD/src/share");
	TDoodad::load_XML(sharePath);
	// Creating GameStateManager and pushing first state
	GameStateManager* gsm = new GameStateManager(window);
	gsm->pushState(new GameStateMenu(), false, false, false);

    while(window.isOpen())
	{
		gsm->initLoop();
        sf::Event event;
        while(window.pollEvent(event))
		{
			switch(event.type)
			{
            case sf::Event::Closed:
                gsm->requestQuit();
                break;
			case sf::Event::MouseButtonPressed:
				gsm->mouseDown(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
				break;
			case sf::Event::MouseButtonReleased:
				gsm->mouseUp(event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
				break;
			case sf::Event::MouseMoved:
				gsm->mouseMove(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseWheelMoved:
				gsm->mouseWheel(event.mouseWheel.delta, event.mouseWheel.x, event.mouseWheel.y);
				break;
			case sf::Event::KeyPressed:
				gsm->keyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				gsm->keyUp(event.key.code);
				break;
            default:
                break;
			}
		}

        float dt = clockwerk.restart().asSeconds();
        dt = MIN(dt,MAXIMAL_FRAME_DURATION);

        gsm->update(dt);

        window.clear();
        gsm->render(window);
        window.display();

        gsm->endLoop(window);
    }

	delete gsm;
	ResourceManager::Destroy();
	delete &window;

    return 0;
}
