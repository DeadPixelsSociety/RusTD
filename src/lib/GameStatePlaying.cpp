#include "../include/GameStatePlaying.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/TDoodad.hpp"

/*explicit*/ GameStatePlaying::GameStatePlaying()
: GameState()
, m_map(nullptr)
{
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

    TTower* tt2 = TDoodad::getTTower(0);
    TTower* tt3 = TDoodad::getTTower(1);

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

    this->t_creep_spawn_cd += dt;
    if(this->t_creep_spawn_cd>=1.5f)
    {
        TCreep* tc = TDoodad::getTCreep(0);

        Creep* new_c = new Creep(tc);
        this->addCreep(new_c);
        this->t_creep_spawn_cd = 0.f;
    }

    this->m_cl->update(dt);
    this->m_tl->update(dt);
    this->m_pl->update(dt);
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
