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
#ifndef TOWER_H
#define TOWER_H

#include "TTower.hpp"
#include "CreepList.hpp"
#include "Projectile.hpp"

const sf::Vector2f COOLDOWN_BAR_RECTANGLE = sf::Vector2f(GRID_UNIT,3.f);
const sf::Vector2f COOLDOWN_BAR_OFFSET = sf::Vector2f(0.f,0.f);

const sf::Color RANGE_INDICATOR_LIMIT_COLOR = sf::Color(100, 255, 150, 150);
const sf::Color RANGE_INDICATOR_ZONE_COLOR = sf::Color(100, 255, 150, 25);

class Tower
{
public:
	Tower(void);
	Tower(TTower* tt, sf::Vector2i position);

	~Tower(void);

    void enableRangeIndicator(bool e);

    void setTarget(Creep* c);

    bool inRange(Creep* c);
    bool canAttack(Creep* c);
    bool isTowerPosition(sf::Vector2i placement);

	Projectile* attackList(CreepList* ac);
    Projectile* attack(Creep* c);

	void update(float dt);
    void render(sf::RenderWindow& window);

protected:
	TTower* m_ttower;
	float m_attack_cooldown, m_proj_speed;
	sf::Vector2i m_position;
	Creep* m_last_target;
	bool m_show_range_indicator;

};

#endif
