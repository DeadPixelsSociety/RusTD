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

const float GRID_UNIT = 64.f;

// Enumeration
enum UnitType
{
	GROUND = 0,
	AIR = 1,
	WATER = 2,
	UNITTYPE_COUNT
};

// Structure
// Tower
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

// Creep
struct Movement
{
	UnitType type;
	float speed;
};

struct Stats
{
	float health, health_regen;
	int bounty;
};

#endif
