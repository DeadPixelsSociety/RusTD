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
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/View.hpp>

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
	virtual sf::View getView(void);
	virtual void setViewPositionX(int px);
	virtual void setViewPositionY(int px);
	virtual void setViewWidth(int px);
	virtual void setViewHeight(int px);

protected:

	sf::View m_view;

};

#endif // GAMESTATE_HPP
