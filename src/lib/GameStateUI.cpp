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
#include "../include/GameStateUI.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

/*explicit*/ GameStateUI::GameStateUI(GameStatePlaying* gsp)
: GameState()
, m_gsp(gsp)
, m_panel(nullptr)
{
	m_panel = new sf::Sprite();
	m_panel->setTexture(*(ResourceManager::Instance()->getTexture("Static Panel Ui")));
	m_panel->setPosition(VIEW_WIDTH * WIDTH_VIEWPORT_COEF - 64.0f, 0.0f);
}

/*virtual*/ GameStateUI::~GameStateUI()
{
	delete m_panel;
}

/*virtual*/ void GameStateUI::update(float deltaTimeInSeconds)
{

}

/*virtual*/ void GameStateUI::render(sf::RenderWindow& window)
{
	window.draw(*m_panel);
}

/*virtual*/ void GameStateUI::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{
	// @TODO : check if a tower is selected
	m_gsp->SetState(PlacingTower);
}

/*virtual*/ void GameStateUI::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStateUI::mouseMove(int positionX, int positionY)
{

}

/*virtual*/ void GameStateUI::mouseWheel(int delta, int positionX, int positionY)
{

}

/*virtual*/ void GameStateUI::keyDown(sf::Keyboard::Key key)
{

}

/*virtual*/ void GameStateUI::keyUp(sf::Keyboard::Key key)
{

}

