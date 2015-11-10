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
#ifndef GAMESTATEUI_HPP
#define GAMESTATEUI_HPP

#include "Button.hpp"
#include "GameState.hpp"
#include "GameStatePlaying.hpp"

class GameStateUI : public GameState
{
public:

	explicit GameStateUI(GameStatePlaying* gsp);
	virtual ~GameStateUI(void);

    TTower* getTTower(void);
    void setTTower(TTower* tt);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseMove(int positionX, int positionY);
	virtual void mouseWheel(int delta, int positionX, int positionY);
	virtual void keyDown(sf::Keyboard::Key key);
	virtual void keyUp(sf::Keyboard::Key key);

    void setSelectedTTower(TTower* tt);

protected:

	GameStatePlaying* m_gsp;
	sf::Sprite* m_panel;
    std::vector<std::pair<Button*,TTower*>> m_aButtonTTower;
    TTower* m_tt;
    sf::Text* m_leaks_text;

};

#endif // GAMESTATEUI_HPP
