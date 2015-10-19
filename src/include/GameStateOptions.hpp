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
