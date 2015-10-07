#ifndef CREEP_LIST_H
#define CREEP_LIST_H

#include <vector>

#include "Creep.hpp"

class CreepList
{
public:
	CreepList(void);

	~CreepList(void);

    int getSize(void);
    Creep* getCreep(int i);

    void addCreep(Creep* cre);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	std::vector<Creep*> m_aCreep;

};

#endif
