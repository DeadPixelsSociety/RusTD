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
#include "../include/TTower.hpp"

TTower::TTower()
: m_id(-1)
, m_name("")
{
	this->m_attack = Attack();
	this->m_attack.damage = 0;
	this->m_attack.speed = 0;
	this->m_attack.range.minimal = 0;
	this->m_attack.range.maximal = 0;
	for(int i=0 ; i<UnitType::UNITTYPE_COUNT ; i++)
	{
		this->m_attack.availableTarget[i] = false;
	}
	this->m_constr = Construction();
	this->m_constr.cost = 0;
	this->m_constr.time = 0;
	this->m_constr.foundation.size = 1;
	this->m_constr.foundation.type = UnitType::GROUND;
}

TTower::TTower(int id, std::string name, Attack attack, Construction constr)
: m_id(id)
, m_name(name)
, m_attack(attack)
, m_constr(constr)
{}

TTower::~TTower()
{}

int TTower::getId() const
{
	return m_id;
}

std::string TTower::getName() const
{
	return m_name;
}

std::vector<int>& TTower::getUpgrades()
{
	return m_upgrades;
}

Attack TTower::getAttack() const
{
    return this->m_attack;
}

Construction TTower::getConstruction() const
{
	return m_constr;
}

void TTower::setIdent(std::string icon, std::string base, std::string head, std::string projectile, std::string splash)
{
	this->m_icon_ident = icon;
	this->m_base_ident = base;
	this->m_head_ident = head;
	this->m_projectile_ident = projectile;
	this->m_splash_ident = splash;
}
