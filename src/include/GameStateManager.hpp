/*

	RusTD - A rusted Tower Defense game
    Copyright (C) 2015  Beuzmoker, Enferium, Farijo, Vizepi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameState;

struct GameStateHandler;

class GameStateManager
{
public:

	explicit GameStateManager(void);
	explicit GameStateManager(sf::RenderWindow& window);
	virtual ~GameStateManager(void);

	virtual void pushState(GameState* state, bool updateSubStates, bool renderSubStates, bool inputSubStates);
	virtual void pushStateHandler(GameStateHandler stateHandler);
	virtual void popState(void);
	virtual GameStateHandler peekState(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseMove(int positionX, int positionY);
	virtual void mouseWheel(int delta, int positionX, int positionY);
	virtual void keyDown(sf::Keyboard::Key key);
	virtual void keyUp(sf::Keyboard::Key key);

	virtual void initLoop(void);
	virtual void endLoop(sf::RenderWindow& window);
	virtual void quit(void);
	virtual void setWindow(sf::RenderWindow& window);
	virtual sf::RenderWindow* getWindow(void);

	virtual void requestQuit(void);

	static GameStateManager* Instance(void);

protected:

	virtual int computeUpdateDepth();
	virtual int computeRenderDepth();
	virtual int computeInputDepth();

	std::vector<GameStateHandler> m_stateStack;
	std::vector<GameState*> m_statesToDelete;

	GameState* m_currentState;
	int m_loopStackSize;

	bool m_pendingDelete;
	bool m_pendingQuit;

	sf::RenderWindow* m_window;

	static GameStateManager* s_instance;

};

/*

	Conception details :

	When starting the game, PushState your first gamestate

	When you change the state, you can popState the current state and then pushState the new state.
	You can also pushState the new state, keeping the previous state on the stack and possibly allowing
	it to udpate and render with the booleans updateSubStates and renderSubStates.

	When you popState a state, the state is automatically destroyed.
	When you peekState a state, the state is removed from the stack but returned, not destroyed.
	The return object is not a GameState, but a GameStateHandler, and that must not being destroyed.
	To remove a peekState'd GameStateHandler, just pushStateHandler it and then popState it.

	The initLoop function is called at the begining of the game loop to load the right GameState
	The endLoop function is called at the end of the game loop to manage the push, pop and peek requests.

*/

#endif // GAMESTATEMANAGER_HPP
