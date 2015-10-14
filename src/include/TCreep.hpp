#ifndef TCREEP_H
#define TCREEP_H

#include "config.hpp"

class TCreep
{
public:
	TCreep(void);
	TCreep(int id, std::string name, Movement movement, Stats stats);

	~TCreep(void);

	int getId(void) const;
	std::string getName(void) const;
    Movement getMovement(void) const;
    Stats getStats(void) const;

protected:
	int m_id;
	std::string m_name;
	Movement m_movement;
	Stats m_stats;
};

#endif
