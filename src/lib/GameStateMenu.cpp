#include "../include/GameStateMenu.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/GameStateManager.hpp"

/*explicit*/ GameStateMenu::GameStateMenu()
: GameState()
, m_buttonPlay(nullptr)
, m_backgroundSprite(nullptr)
{
	ResourceManager* resources = ResourceManager::Instance();
	sf::Texture* backgroundTexture = resources->registerTexture("data/texture/testBackground.png", "Menu Background");
	sf::Font* font = resources->registerFont("data/font/Hanken-Book.ttf", "Global Font");
	m_backgroundSprite = new sf::Sprite(*backgroundTexture);
	m_buttonPlay = new Button(150, 50, "Play", *font, 30, sf::Color::Transparent, sf::Color::White);
	m_buttonPlay->setPosition(sf::Vector2f(725, 425));
}

/*virtual*/ GameStateMenu::~GameStateMenu()
{
	ResourceManager* resources = ResourceManager::Instance();
	resources->releaseTexture("Menu Background");
}

/*virtual*/ void GameStateMenu::update(float deltaTimeInSeconds)
{

}

/*virtual*/ void GameStateMenu::render(sf::RenderWindow& window)
{
	window.draw(*m_backgroundSprite);
	m_buttonPlay->render(window);
}

/*virtual*/ void GameStateMenu::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
	if(button == sf::Mouse::Left && m_buttonPlay->isInButton(positionX, positionY))
	{
		GameStateManager::Instance()->quit();
	}
}
