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
#ifndef GAMESTATEPLAYING_HPP
#define GAMESTATEPLAYING_HPP

#include "GameState.hpp"
#include "Map.hpp"
#include "TowerList.hpp"
#include "CreepList.hpp"
#include "ProjectileList.hpp"
#include "Random.hpp"
#include <vector>
#include <SFML/Graphics/View.hpp>

#define WIDTH_VIEWPORT_COEF 0.8f
#define SCROLL_PERCENT 0.1f
#define SCROLL_MAX_SPEED 750.0f

#define LEVEL_WIDTH 2560
#define LEVEL_HEIGHT 1800

class GameStateUI;

enum class PlayingState
{
	Normal,
	PlacingTower,
	TowerSelected
};

class GameStatePlaying : public GameState
{
public:

	explicit GameStatePlaying(void);
	virtual ~GameStatePlaying(void);

    GameStateUI getUI(void);
	int getLeak(void);

    void addCreep(Creep* cre);
    void addTower(Tower* tow);

	virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseMove(int positionX, int positionY);
	virtual void mouseWheel(int delta, int positionX, int positionY);
	virtual void keyDown(sf::Keyboard::Key key);
	virtual void keyUp(sf::Keyboard::Key key);
	virtual void SetState(PlayingState state);
	virtual PlayingState GetState(void) const;

	void isPlacementAvailable();
	void creepLeak();

protected:

	CreepList* m_cl;
    ProjectileList* m_pl;
    TowerList* m_tl;
    std::vector<sf::Vector2i> m_path;
	std::vector<Tower*> m_towers;
	std::vector<TTower*> m_ttowers;
	Map* m_map;
	GameStateUI* m_ui;
	std::vector<float> m_zoomCoefs;
	int m_currentZoom;
	sf::View m_view;
	PlayingState m_state;
	sf::Vector2f m_placementPosition;
	sf::Sprite* m_placeTower;
	bool m_placementValid;
	int m_leaks;

    float t_creep_spawn_cd; // @TOREMOVE
};

#endif // GAMESTATEPLAYING_HPP
