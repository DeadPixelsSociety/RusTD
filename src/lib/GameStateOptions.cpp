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

