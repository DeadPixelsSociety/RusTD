#ifndef GAMESTATEOPTIONS_HPP
#define GAMESTATEOPTIONS_HPP

#include "GameState.hpp"
#include "Button.hpp"
#include <SFML/Graphics/Sprite.hpp>

class GameStateOptions : public GameState
{
public:

	explicit GameStateOptions(void);
	virtual ~GameStateOptions(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);

	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void keyUp(sf::Keyboard::Key key);

protected:

	sf::Sprite* m_background;
	Button* m_backButton;

};

#endif // GAMESTATEOPTIONS_HPP
