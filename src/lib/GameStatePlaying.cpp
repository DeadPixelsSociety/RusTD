#include "../include/GameStatePlaying.hpp"
#include "../include/GameStateManager.hpp"

/*explicit*/ GameStatePlaying::GameStatePlaying()
: GameState()
, m_level(nullptr)
{
	m_level = new Level();
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

    TTower tt = TTower(1, "Tour de garde", att, cons);

    m_towers.push_back(new Tower(&tt, sf::Vector2i(10,8)));
    m_level->addTower(m_towers.back());
    m_towers.push_back(new Tower(&tt, sf::Vector2i(1,1)));
    m_level->addTower(m_towers.back());
    m_towers.push_back(new Tower(&tt, sf::Vector2i(0,0)));
    m_level->addTower(m_towers.back());
    m_towers.push_back(new Tower(&tt, sf::Vector2i(5,5)));
    m_level->addTower(m_towers.back());
}

/*virtual*/ GameStatePlaying::~GameStatePlaying()
{
	delete m_level;
	for(std::vector<Tower*>::iterator it = m_towers.begin(); it != m_towers.end(); ++it)
	{
		delete *it;
	}
}

/*virtual*/ void GameStatePlaying::update(float deltaTimeInSeconds)
{
	m_level->update(deltaTimeInSeconds);
}

/*virtual*/ void GameStatePlaying::render(sf::RenderWindow& window)
{
	m_level->render(window);
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
