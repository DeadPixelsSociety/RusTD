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
#include "../include/TCreep.hpp"

TCreep::TCreep(void)
{
	this->m_id = -1;
	this->m_name = "";
	this->m_movement = Movement();
	this->m_movement.type = UnitType::GROUND;
	this->m_movement.speed = 0;
	this->m_stats = Stats();
	this->m_stats.health = 1;
	this->m_stats.health_regen = 0;
	this->m_stats.bounty = 0;
}

TCreep::TCreep(int id, std::string name, Movement movement, Stats stats)
{
	this->m_id = id;
	this->m_name = name;
	this->m_movement = movement;
	this->m_stats = stats;
}

TCreep::~TCreep(void)
{}

int TCreep::getId() const
{
	return m_id;
}

std::string TCreep::getName() const
{
	return m_name;
}

Movement TCreep::getMovement(void) const
{
    return this->m_movement;
}

Stats TCreep::getStats(void) const
{
    return this->m_stats;
}
