#ifndef TOWER_LIST_H
#define TOWER_LIST_H

#include <vector>

#include "Tower.hpp"
#include "ProjectileList.hpp"

class TowerList
{
public:
	TowerList(void);

	~TowerList(void);

    //int getSize(void);
    //Creep* getTower(int i);

    void addTower(Tower* tow);

	void attackList(ProjectileList* ap,CreepList* ac);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	std::vector<Tower*> m_aTower;

};

#endif
