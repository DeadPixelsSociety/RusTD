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

	Attack getAttack(void);

protected:
	int m_id;
	std::string m_name;
	std::vector<TTower*> m_upgrades;
	Attack m_attack;
	float m_proj_speed;
	Construction m_constr;
};

#endif
