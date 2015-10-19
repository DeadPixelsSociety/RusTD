/*

	RusTD - A rusted Tower Defense game
    Copyright (C) 2015  Beuzmoker, Enferium, Farijo, Vizepi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <SFML/Graphics.hpp>

#include "../include/tools.hpp"
#include "../include/Window.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/ResourceLoading.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/GameStateMenu.hpp"
#include "../include/TDoodad.hpp"
#include "../include/Random.hpp"

#include <iostream>
#include <fstream>

constexpr float MAXIMAL_FRAME_DURATION = 1/15.f;

int main()
{
#if defined _DEBUG && ENTITIES_LOADING_MODE == LOAD_BIN
	std::ifstream data_check("data.bin", std::ios::binary);
	if(!data_check.good())
	{
		system("DC");
	}
	data_check.close();
#endif // _DEBUG

	// Initializing window
	Window::Initialize();
    sf::RenderWindow& window = *(new sf::RenderWindow(Window::windowedVideoMode, GAME_TITLE, sf::Style::Titlebar | sf::Style::Close));
    resizeWindow(window, Window::windowedVideoMode.width, Window::windowedVideoMode.height);
    window.setFramerateLimit(120);

    // Seed random class
    Random::SetSeed(time(NULL));

    // frame time counter
    sf::Clock clockwerk;
    // Initializing resources
	ResourceManager::Initialize();

#if ENTITIES_LOADING_MODE == LOAD_XML
	// Load doodad from xml files
	TDoodad::load_XML(SHARE_DIR);
	// Load resources from data directory
	LoadResources();
#else // ENTITIES_LOADING_MODE != LOAD_XML
	// Load doodad from binary file
	Data* data = new Data("data.bin");
	data->freeTextures();
	data->freeFonts();
	data->freeSounds();
	TDoodad::load_Data(*data);
	// Load resources from binary file
	LoadResources(data);
#endif // ENTITIES_LOADING_MODE = LOAD_XML

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
	TDoodad::destroy_objects();
	delete &window;
#if ENTITIES_LOADING_MODE == LOAD_BIN
	delete data;
#endif // ENTITIES_LOADING_MODE

    return 0;
}
