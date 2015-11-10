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
#ifndef CREEP_LIST_H
#define CREEP_LIST_H

#include <vector>

#include "Creep.hpp"

class CreepList
{
public:
	CreepList(void);

	~CreepList(void);

    int getSize(void);
    Creep* getCreep(int i);

    void addCreep(Creep* cre);
    void removeCreep(Creep* cre);

    void creepLeak(sf::Vector2i pos);

	void update(float dt);
	void renderCreep(sf::RenderWindow& window);
	void renderDialog(sf::RenderWindow& window);

protected:
	std::vector<Creep*> m_aCreep;

};

#endif
