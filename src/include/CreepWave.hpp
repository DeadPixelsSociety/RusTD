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
#ifndef CREEP_WAVE_H
#define CREEP_WAVE_H

#include "TCreep.hpp"

class CreepWave
{
public:
	CreepWave(void);
	CreepWave(TCreep* tc, unsigned int amount, unsigned int rank);

	~CreepWave(void);

	TCreep* getTCreep(void);
	unsigned int getCreepRank(void);

	void decrementCreepAmount(void);
	bool isCreepRemaining(void);

protected:
	TCreep* m_tcreep;
	int m_creep_amount;
	unsigned int m_creep_rank;
};

#endif



