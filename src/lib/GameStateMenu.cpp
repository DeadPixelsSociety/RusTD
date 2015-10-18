#include "../include/GameStateMenu.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/GameStatePlaying.hpp"
#include "../include/GameStateOptions.hpp"
#include "../include/tools.hpp"
#include "../include/Window.hpp"

/*explicit*/ GameStateMenu::GameStateMenu()
: GameState()
, m_buttonPlay(nullptr)
, m_buttonOption(nullptr)
, m_backgroundSprite(nullptr)
, m_mouseInOptions(false)
{
	ResourceManager* resources = ResourceManager::Instance();
	m_backgroundSprite = new sf::Sprite(*(resources->getTexture("Menu Background")));
	m_buttonPlay = new Button(150, 50, "Play", *(resources->getFont("Global Font")), 30, sf::Color::Transparent, sf::Color::White);
	m_buttonPlay->setPosition(sf::Vector2f(725, 425));
	m_buttonOption = new Button(resources->getTexture("Static Gear"), "", *(resources->getFont("Global Font")), 30);
	m_buttonOption->setPosition(sf::Vector2f(VIEW_WIDTH - 128, VIEW_HEIGHT - 128));
	m_buttonOption->getShape()->setOrigin(m_buttonOption->getShape()->getLocalBounds().width / 2, m_buttonOption->getShape()->getLocalBounds().height / 2);
}

/*virtual*/ GameStateMenu::~GameStateMenu()
{
	delete m_backgroundSprite;
	delete m_buttonPlay;
	delete m_buttonOption;
}

/*virtual*/ void GameStateMenu::update(float deltaTimeInSeconds)
{
	if(m_mouseInOptions)
	{
		sf::RectangleShape* rs = m_buttonOption->getShape();
		if(rs)rs->rotate(180.f * deltaTimeInSeconds);
	}
}

/*virtual*/ void GameStateMenu::render(sf::RenderWindow& window)
{
	window.draw(*m_backgroundSprite);
	m_buttonPlay->render(window);
	m_buttonOption->render(window);
}

/*virtual*/ void GameStateMenu::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
	if(button == sf::Mouse::Left)
	{
		if(m_buttonPlay->isInButton(positionX, positionY))
		{
			GameStateManager::Instance()->pushState(new GameStatePlaying(), false, false, false);
		}
		else if(m_buttonOption->isInButton(positionX, positionY))
		{
			m_mouseInOptions = false;
			sf::RectangleShape* rs = m_buttonOption->getShape();
			if(rs)rs->setRotation(0.f);
			//GameStateManager::Instance()->requestQuit();
			GameStateManager::Instance()->pushState(new GameStateOptions(), false, false, false);
		}
	}
}

/*virtual*/ void GameStateMenu::mouseMove(int positionX, int positionY)
{
	if(m_buttonOption->isInButton(positionX, positionY))
	{
		m_mouseInOptions = true;
	}
	else
	{
		m_mouseInOptions = false;
		sf::RectangleShape* rs = m_buttonOption->getShape();
		if(rs)rs->setRotation(0.f);
	}
}

/*virtual*/ void GameStateMenu::keyUp(sf::Keyboard::Key key)
{
	switch(key)
	{
	case sf::Keyboard::Escape:
		GameStateManager::Instance()->requestQuit();
		break;
	case sf::Keyboard::F:
		switchFullScreen(GameStateManager::Instance()->getWindow(), !Window::isFullScreen);
		break;
	default:
		break;
	}
}
