#include <SFML/Graphics.hpp>

#include "../include/tools.hpp"
#include "../include/Window.hpp"
#include "../include/Level.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/GameStateMenu.hpp"

#include <iostream>

constexpr float MAXIMAL_FRAME_DURATION = 1/15.f;

int main()
{

    ////////////////////////////////////
    /*Attack att = Attack();
    Range ran = Range();
    ran.minimal = 0.f;
    ran.maximal = 200.f;
    att.range = ran;
    att.damage = 0.03f;
    att.speed = 0.01f;
    att.availableTarget[UnitType::GROUND] = true;
    att.availableTarget[UnitType::AIR] = false;
    att.availableTarget[UnitType::WATER] = true;

    Construction cons = Construction();
    Foundation found = Foundation();
    found.size = 1;
    found.type = UnitType::GROUND;
    cons.cost = 1.f;
    cons.time = 0.f;
    cons.foundation = found;

    TTower tt = TTower(1, "Tour de garde", att, cons);*/

    ////////////////////////////////////
    /*
    Movement move = Movement();
    move.speed = 100.f;
    move.type = UnitType::GROUND;

    Stats sta = Stats();
    sta.bounty = 3;
    sta.health = 9.f;
    sta.health_regen = 0.f;

    TCreep tc = TCreep(1, "Monstre", move, sta);
    */

    ////////////////////////////////////
    ////////////////////////////////////
    ////////////////////////////////////

    /*Level* lev = new Level();

    Tower* t = new Tower(&tt, sf::Vector2i(10,8));
    Tower* t2 = new Tower(&tt, sf::Vector2i(1,1));
    Tower* t3 = new Tower(&tt, sf::Vector2i(0,0));
    Tower* t4 = new Tower(&tt, sf::Vector2i(5,5));

    lev->addTower(t);
    lev->addTower(t2);
    lev->addTower(t3);
    lev->addTower(t4);*/

	// Initializing window
	Window::Initialize();
    sf::RenderWindow& window = *(new sf::RenderWindow(Window::windowedVideoMode, GAME_TITLE, sf::Style::Titlebar | sf::Style::Close));
    resizeWindow(window, Window::windowedVideoMode.width, Window::windowedVideoMode.height);
    window.setFramerateLimit(300);
    // frame time counter
    sf::Clock clockwerk;
    // Initializing resources
	ResourceManager::Initialize();
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

        //
        gsm->update(dt);
        //lev->update(dt);

        window.clear();
        gsm->render(window);
        //lev->render(window);
        window.display();
        gsm->endLoop(window);
    }

	delete gsm;
	ResourceManager::Destroy();
	delete &window;

    return 0;
}
