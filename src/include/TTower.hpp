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

protected:
	int m_id;
	std::string m_name;
	std::vector<int> m_upgrades;
	Attack m_attack;
	Construction m_constr;
};

#endif
