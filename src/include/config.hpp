#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define GAME_TITLE "RusTD"

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
