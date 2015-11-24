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
#ifndef TTOWER_H
#define TTOWER_H

#include <vector>

#include "config.hpp"

struct Range
{
	float minimal, maximal;
};

struct Attack
{
	float damage, speed;
	Range range;
	bool availableTarget[UnitType::UNITTYPE_COUNT];
};

struct Foundation
{
	int size;
	UnitType type;
};

struct Construction
{
	int cost;
	float time;
	Foundation foundation;
};

class TTower
{
public:
	TTower(void);
	TTower(int id, std::string name, Attack attack, Construction constr);

	~TTower(void);

	int getId(void) const;
	std::string getName(void) const;
	std::vector<int>& getUpgrades(void);
	Attack getAttack(void) const;
	Construction getConstruction(void) const;
	void setIdent(std::string icon, std::string base, std::string head, std::string projectile, std::string splash);

protected:
	int m_id;
	std::string m_name;
	std::vector<int> m_upgrades;
	Attack m_attack;
	Construction m_constr;
	std::string m_icon_ident;
	std::string m_base_ident;
	std::string m_head_ident;
	std::string m_projectile_ident;
	std::string m_splash_ident;

};

#endif
