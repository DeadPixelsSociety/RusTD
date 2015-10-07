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

Movement TCreep::getMovement(void)
{
    return this->m_movement;
}

Stats TCreep::getStats(void)
{
    return this->m_stats;
}
