#include <SFML/Graphics.hpp>

#include "../include/tools.hpp"
#include "../include/Level.hpp"

constexpr float MAXIMAL_FRAME_DURATION = 1/15.f;

int main()
{
    ////////////////////////////////////
    Attack att = Attack();
    Range ran = Range();
    ran.minimal = 0.f;
    ran.maximal = 200.f;
    att.range = ran;
    att.damage = 0.01f;
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

    TTower tt = TTower(1, "Tour de garde", att, cons);

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

    Level* lev = new Level();

    Tower* t = new Tower(&tt, sf::Vector2i(10,8));
    Tower* t2 = new Tower(&tt, sf::Vector2i(1,1));
    Tower* t3 = new Tower(&tt, sf::Vector2i(0,0));
    Tower* t4 = new Tower(&tt, sf::Vector2i(5,5));

    lev->addTower(t);
    lev->addTower(t2);
    lev->addTower(t3);
    lev->addTower(t4);

    sf::RenderWindow window(sf::VideoMode(800,450), "RusTD");
    window.setFramerateLimit(60);
    sf::Clock clockwerk;

    while(window.isOpen())
	{
        sf::Event event;
        while(window.pollEvent(event))
		{
			switch(event.type)
			{
            case sf::Event::Closed:
                window.close();
                break;
			case sf::Event::Resized:
				resizeWindow(window, event.size.width, event.size.height);
				break;
            default:
                break;
			}
		}

        float dt = clockwerk.restart().asSeconds();
        dt = MIN(dt,MAXIMAL_FRAME_DURATION);

        //
        lev->update(dt);

        window.clear();
        lev->render(window);
        window.display();
    }

    return 0;
}
