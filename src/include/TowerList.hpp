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
#ifndef TOWER_LIST_H
#define TOWER_LIST_H

#include <vector>

#include "Tower.hpp"
#include "ProjectileList.hpp"

class TowerList
{
public:
	TowerList(void);

	~TowerList(void);

    //int getSize(void);
    Tower* getTower(int i);

    void addTower(Tower* tow);

	void attackList(ProjectileList* ap,CreepList* ac);
	bool isPlacementAvailable(sf::Vector2i placement);
    Tower* findTowerAtPosition(sf::Vector2i position);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	std::vector<Tower*> m_aTower;

};

#endif
