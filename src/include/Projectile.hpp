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
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "config.hpp"
#include "Creep.hpp"

class Projectile
{
public:
	Projectile(void);
	Projectile(float speed, float damage, Creep* target, sf::Vector2f position);

	~Projectile(void);

    sf::Vector2f getPosition(void);
    int getState(void);
    Creep* getTarget(void);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	float m_speed, m_damage;
	Creep* m_target;
	sf::Vector2f m_position;
    sf::Vector2i m_target_sign;
    int m_state;

};

#endif
