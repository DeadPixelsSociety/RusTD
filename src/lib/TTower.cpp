#include "../include/TTower.hpp"

TTower::TTower()
{
	this->m_id = -1;
	this->m_name = "";
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
{
	this->m_id = id;
	this->m_name = name;
	this->m_attack = attack;
	this->m_constr = constr;
}

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
