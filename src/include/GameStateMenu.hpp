#ifndef GAMESTATEMENU_HPP
#define GAMESTATEMENU_HPP

#include "GameState.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Sprite.hpp>

class GameStateMenu : public GameState
{
public:

	explicit GameStateMenu(void);
	virtual ~GameStateMenu(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void keyUp(sf::Keyboard::Key);

protected:

	Button* m_buttonPlay;
	sf::Sprite* m_backgroundSprite;

};

#endif // GAMESTATEMENU_HPP
