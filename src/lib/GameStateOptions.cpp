#include "../include/GameStateOptions.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/GameStateManager.hpp"

/*explicit*/ GameStateOptions::GameStateOptions()
: GameState()
, m_background(nullptr)
, m_backButton(nullptr)
{
	m_background = new sf::Sprite(*(ResourceManager::Instance()->getTexture("Static Option Background")));
}

/*virtual*/ GameStateOptions::~GameStateOptions()
{
	delete m_background;
}

/*virtual*/ void GameStateOptions::update(float deltaTimeInSeconds)
{

}

/*virtual*/ void GameStateOptions::render(sf::RenderWindow& window)
{
	window.draw(*m_background);
}

/*virtual*/ void GameStateOptions::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStateOptions::keyUp(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::Escape:
		GameStateManager::Instance()->popState();
		break;
	default:
		break;
	}
}

