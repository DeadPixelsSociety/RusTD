#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameState
{
public:

	explicit GameState(void){}
	virtual ~GameState(void){}

	virtual void update(float deltaTimeInSeconds) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY){}
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY){}
	virtual void mouseMove(int positionX, int positionY){}
	virtual void mouseWheel(int delta, int positionX, int positionY){}
	virtual void keyDown(sf::Keyboard::Key key){}
	virtual void keyUp(sf::Keyboard::Key key){}

protected:

};

#endif // GAMESTATE_HPP
