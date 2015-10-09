#ifndef GAMESTATEPLAYING_HPP
#define GAMESTATEPLAYING_HPP

#include "GameState.hpp"
#include "Level.hpp"
#include <vector>

class GameStatePlaying : public GameState
{
public:

	explicit GameStatePlaying(void);
	virtual ~GameStatePlaying(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseMove(int positionX, int positionY);
	virtual void mouseWheel(int delta, int positionX, int positionY);
	virtual void keyDown(sf::Keyboard::Key key);
	virtual void keyUp(sf::Keyboard::Key key);

protected:

	Level* m_level;
	std::vector<Tower*> m_towers;

};

#endif // GAMESTATEPLAYING_HPP
