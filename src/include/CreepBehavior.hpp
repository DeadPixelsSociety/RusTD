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
#ifndef CREEP_BEHAVIOR_H
#define CREEP_BEHAVIOR_H

#include <SFML/Graphics/Sprite.hpp>

class CreepBehavior
{
public:
	CreepBehavior(void);

	~CreepBehavior(void);

protected:
	float m_movement_coefficient;
	float m_damage_over_time;
    bool m_confusion;
    sf::Sprite* m_sprite;
};

#endif
