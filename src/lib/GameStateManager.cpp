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
#include "../include/GameStateManager.hpp"
#include "../include/GameState.hpp"
#include "../include/config.hpp"
#include "../include/GameStateQuestionBox.hpp"

struct GameStateHandler
{
	GameStateHandler():m_gameState(nullptr),m_updateSubStates(false),m_renderSubStates(false),m_inputSubStates(false){}
	GameState* m_gameState;
	bool m_updateSubStates;
	bool m_renderSubStates;
	bool m_inputSubStates;
};

/*explicit*/ GameStateManager::GameStateManager()
: m_currentState(nullptr)
, m_loopStackSize(0)
, m_pendingDelete(false)
, m_pendingQuit(false)
, m_window(nullptr)
{
	s_instance = this;
}

/*explicit*/ GameStateManager::GameStateManager(sf::RenderWindow& window)
: m_currentState(nullptr)
, m_loopStackSize(0)
, m_pendingDelete(false)
, m_pendingQuit(false)
, m_window(&window)
{
	s_instance = this;
}

/*virtual*/ GameStateManager::~GameStateManager()
{}

/*virtual*/ void GameStateManager::pushState(GameState* state, bool updateSubStates, bool renderSubStates, bool inputSubStates)
{
	GameStateHandler gsh;
	gsh.m_gameState = state;
	gsh.m_updateSubStates = updateSubStates;
	gsh.m_renderSubStates = renderSubStates;
	gsh.m_inputSubStates = inputSubStates;
	m_stateStack.push_back(gsh);
}

/*virtual*/ void GameStateManager::pushStateHandler(GameStateHandler stateHandler)
{
	m_stateStack.push_back(stateHandler);
}

/*virtual*/ void GameStateManager::popState()
{
	if(m_stateStack.size() > 0)
	{
		if(m_stateStack.back().m_gameState == m_currentState)
		{
			m_pendingDelete = true;
		}
		m_stateStack.pop_back();
		if((int)m_stateStack.size() < m_loopStackSize)
		{
			m_loopStackSize = m_stateStack.size();
		}
	}
}

/*virtual*/ GameStateHandler GameStateManager::peekState()
{
	if(m_stateStack.size() <= 0)
	{
		return GameStateHandler();
	}
	GameStateHandler gsh = m_stateStack.back();
	m_stateStack.pop_back();
	if((int)m_stateStack.size() < m_loopStackSize)
	{
		m_loopStackSize = m_stateStack.size();
	}
	return gsh;
}

/*virtual*/ void GameStateManager::update(float deltaTimeInSeconds)
{
	if(m_currentState != nullptr)
	{
		int depth = computeUpdateDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->update(deltaTimeInSeconds);
		}
		m_currentState->update(deltaTimeInSeconds);
	}
}

/*virtual*/ void GameStateManager::render(sf::RenderWindow& window)
{
	if(m_currentState != nullptr)
	{
		int depth = computeRenderDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->render(window);
		}
		m_currentState->render(window);
	}
}

/*virtual*/ void GameStateManager::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->mouseDown(button, positionX, positionY);
		}
		m_currentState->mouseDown(button, positionX, positionY);
	}
}

/*virtual*/ void GameStateManager::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->mouseUp(button, positionX, positionY);
		}
		m_currentState->mouseUp(button, positionX, positionY);
	}
}

/*virtual*/ void GameStateManager::mouseMove(int positionX, int positionY)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->mouseMove(positionX, positionY);
		}
		m_currentState->mouseMove(positionX, positionY);
	}
}

/*virtual*/ void GameStateManager::mouseWheel(int delta, int positionX, int positionY)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->mouseWheel(delta, positionX, positionY);
		}
		m_currentState->mouseWheel(delta, positionX, positionY);
	}
}

/*virtual*/ void GameStateManager::keyDown(sf::Keyboard::Key key)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->keyDown(key);
		}
		m_currentState->keyDown(key);
	}
}

/*virtual*/ void GameStateManager::keyUp(sf::Keyboard::Key key)
{
	if(m_currentState != nullptr)
	{
		int depth = computeInputDepth();
		for(int i = depth; i < m_loopStackSize; ++i)
		{
			m_stateStack[i].m_gameState->keyUp(key);
		}
		m_currentState->keyUp(key);
	}
}

/*virtual*/ void GameStateManager::initLoop()
{
	if(m_stateStack.size() > 0)
	{
		m_currentState = m_stateStack.back().m_gameState;
		m_loopStackSize = m_stateStack.size() - 1;
	}
}

/*virtual*/ void GameStateManager::endLoop(sf::RenderWindow& window)
{
	if(m_pendingDelete)
	{
		delete m_currentState;
	}
	m_pendingDelete = false;
	m_currentState = nullptr;
	m_loopStackSize = 0;
	if(m_pendingQuit)
	{
		window.close();
	}
	m_pendingQuit = false;
}

/*virtual*/ void GameStateManager::quit()
{
	m_pendingQuit = true;
}

/*virtual*/ void GameStateManager::setWindow(sf::RenderWindow& window)
{
	m_window = &window;
}

/*virtual*/ sf::RenderWindow* GameStateManager::getWindow()
{
	return m_window;
}

/*virtual*/ void GameStateManager::requestQuit()
{
	const char* buttons[] = {"Yes", "No"};
	std::function<void(int,void*)> callback =
		[this] (int index, void* data) -> void
		{
			if(index == 0)
			{
				GameStateManager::Instance()->quit(); // Quit game
			}
			else
			{
				GameStateManager::Instance()->popState(); // Pop this state
			}
		};
	GameStateQuestionBox* qb = new GameStateQuestionBox("Do you really want to quit ?", 2, buttons, callback, nullptr);
	pushState(qb, false, true, false);
}

/*static*/ GameStateManager* GameStateManager::Instance()
{
	return s_instance;
}

/*virtual*/ int GameStateManager::computeUpdateDepth()
{
	int depth = m_loopStackSize;
	while(depth > 0)
	{
		if(m_stateStack[depth].m_updateSubStates)
		{
			depth--;
		}
		else
		{
			break;
		}
	}
	return MAX(depth, 0);
}

/*virtual*/ int GameStateManager::computeRenderDepth()
{
	int depth = m_loopStackSize;
	while(depth > 0)
	{
		if(m_stateStack[depth].m_renderSubStates)
		{
			depth--;
		}
		else
		{
			break;
		}
	}
	return MAX(depth, 0);
}

/*virtual*/ int GameStateManager::computeInputDepth()
{
	int depth = m_loopStackSize;
	while(depth > 0)
	{
		if(m_stateStack[depth].m_inputSubStates)
		{
			depth--;
		}
		else
		{
			break;
		}
	}
	return MAX(depth, 0);
}

/*static*/ GameStateManager* GameStateManager::s_instance = nullptr;
