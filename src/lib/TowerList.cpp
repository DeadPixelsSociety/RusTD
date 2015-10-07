#include "../include/TowerList.hpp"

TowerList::TowerList(void)
{}

TowerList::~TowerList(void)
{}

void TowerList::addTower(Tower* tow)
{
    this->m_aTower.push_back(tow);
}

void TowerList::attackList(ProjectileList* ap,CreepList* ac)
{
    int i;
	int size = this->m_aTower.size();
	for(i=0 ; i<size ; i++)
	{
	    Projectile* p = this->m_aTower[i]->attackList(ac);
        if(p!=nullptr)
        {
            ap->addProjectile(p);
        }
	}
}

void TowerList::update(float dt)
{
    int i;
	int size = this->m_aTower.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aTower[i]->update(dt);
	}
}

void TowerList::render(sf::RenderWindow& window)
{
    int i;
	int size = this->m_aTower.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aTower[i]->render(window);
	}
}

