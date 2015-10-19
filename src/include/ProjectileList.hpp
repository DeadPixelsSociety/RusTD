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
#ifndef PROJECTILE_LIST_H
#define PROJECTILE_LIST_H

#include <vector>

#include "Projectile.hpp"

class ProjectileList
{
public:
	ProjectileList(void);

	~ProjectileList(void);

    bool isEmpty(void);

    void addProjectile(Projectile* proj);
    void removeProjectile(Projectile* proj);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	std::vector<Projectile*> m_aProjectile;

};

#endif
