#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

#define SHARE_DIR "../src/share" // !! No ending '/'
#define DATA_DIR "data/" // !! With ending '/'

#define LOAD_XML 0
#define LOAD_BIN 1

#define ENTITIES_LOADING_MODE LOAD_XML // Use LOAD_BIN only if data are compiled in data directory

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
