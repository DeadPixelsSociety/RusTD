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
#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

#define SHARE_DIR "../src/share" // !! No ending '/'
#define DATA_DIR "data/" // !! With ending '/'

#define LOAD_XML 0
#define LOAD_BIN 1

#define ENTITIES_LOADING_MODE LOAD_BIN // Use LOAD_BIN only if data are compiled in data directory

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define GAME_TITLE "RusTD"

#define GRID_UNIT 64

// Enumeration
enum UnitType
{
	GROUND = 0,
	AIR = 1,
	WATER = 2,
	UNITTYPE_COUNT
};

#endif
