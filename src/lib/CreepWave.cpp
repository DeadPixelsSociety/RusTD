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

#include "../include/CreepWave.hpp"

CreepWave::CreepWave(void)
: CreepWave(nullptr,0,0)
{}

CreepWave::CreepWave(TCreep* tc, unsigned int amount, unsigned int rank)
: m_tcreep(tc)
, m_creep_amount(amount)
, m_creep_rank(rank)
{}

CreepWave::~CreepWave(void)
{}

TCreep* CreepWave::getTCreep(void)
{
	return this->m_tcreep;
}

unsigned int CreepWave::getCreepRank(void)
{
	return this->m_creep_rank;
}

void CreepWave::decrementCreepAmount(void)
{
	this->m_creep_amount--;
}

bool CreepWave::isCreepRemaining(void)
{
    return this->m_creep_amount>0;
}
