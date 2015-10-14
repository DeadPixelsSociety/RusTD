#include "../include/GameStatePlaying.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/TDoodad.hpp"

/*explicit*/ GameStatePlaying::GameStatePlaying()
: GameState()
//, m_level(nullptr)
, m_map(nullptr)
{
	//m_level = new Level();
	/*
	Attack att = Attack();
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
*/
    this->m_cl = new CreepList();
    this->m_pl = new ProjectileList();
    this->m_tl = new TowerList();
    this->m_path.push_back(sf::Vector2i(2,-1));
    this->m_path.push_back(sf::Vector2i(2,2));
    this->m_path.push_back(sf::Vector2i(5,2));
    this->m_path.push_back(sf::Vector2i(5,5));
    this->m_path.push_back(sf::Vector2i(10,5));
    this->m_path.push_back(sf::Vector2i(10,2));
    this->m_path.push_back(sf::Vector2i(7,2));
    this->m_path.push_back(sf::Vector2i(7,12));
//
    this->t_creep_spawn_cd = 100000.f;

    Random::SetSeed(time(NULL));

    //TTower tt = TTower(1, "Tour de garde", att, cons);

    TTower* tt2 = TDoodad::getTower(0);
    TTower* tt3 = TDoodad::getTower(1);

    m_towers.push_back(new Tower(tt2, sf::Vector2i(10,8)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt2, sf::Vector2i(1,1)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt2, sf::Vector2i(0,0)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt3, sf::Vector2i(5,6)));
    this->addTower(m_towers.back());
    m_map = new Map(25, 15, this->m_path);
}

/*virtual*/ GameStatePlaying::~GameStatePlaying()
{
	//delete m_level;
	for(std::vector<Tower*>::iterator it = m_towers.begin(); it != m_towers.end(); ++it)
	{
		delete *it;
	}
	delete m_map;
}

void GameStatePlaying::addCreep(Creep* cre)
{
    cre->setPath(this->m_path);
    this->m_cl->addCreep(cre);
}

void GameStatePlaying::addTower(Tower* tow)
{
    this->m_tl->addTower(tow);
}

/*virtual*/ void GameStatePlaying::update(float dt)
{
    this->m_tl->attackList(this->m_pl,this->m_cl);
//
    this->t_creep_spawn_cd += dt;
    if(this->t_creep_spawn_cd>=1.5f)
    {
        Movement move = Movement();
        move.speed = 100.f;

        //int rand_creep_index = Random::NextInt(0, 1);
        move.type = UnitType::GROUND;
/*
        if(rand_creep_index==0)
        {
            //move.type = UnitType::AIR;
        }
*/
        Stats sta = Stats();
        sta.bounty = 3;
        sta.health = 11.f;
        sta.health_regen = 0.f;
        TCreep* tc = new TCreep(1, "Monstre", move, sta);

        Creep* new_c = new Creep(tc);
        this->addCreep(new_c);
        this->t_creep_spawn_cd = 0.f;
    }
//

    this->m_cl->update(dt);
    this->m_tl->update(dt);
    this->m_pl->update(dt);
	//m_level->update(deltaTimeInSeconds);
}

/*virtual*/ void GameStatePlaying::render(sf::RenderWindow& window)
{
	window.draw(sf::Sprite(*(this->m_map->getTexture())));
	this->m_cl->render(window);
    this->m_tl->render(window);
    this->m_pl->render(window);
}

/*virtual*/ void GameStatePlaying::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseMove(int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseWheel(int delta, int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::keyDown(sf::Keyboard::Key key)
{

}

/*virtual*/ void GameStatePlaying::keyUp(sf::Keyboard::Key key)
{
	if(key == sf::Keyboard::Escape)
	{
		GameStateManager::Instance()->popState();
	}
}
