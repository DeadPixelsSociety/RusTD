#include "../include/CreepList.hpp"

CreepList::CreepList(void)
{}

CreepList::~CreepList(void)
{}

int CreepList::getSize(void)
{
    return this->m_aCreep.size();
}

Creep* CreepList::getCreep(int i)
{
    return this->m_aCreep[i];
}

void CreepList::addCreep(Creep* cre)
{
    this->m_aCreep.push_back(cre);
}

void CreepList::update(float dt)
{
    int i;
	int size = this->m_aCreep.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aCreep[i]->update(dt);
		if(this->m_aCreep[i]->getState()>0 && !this->m_aCreep[i]->isChasedByProjectile())
        {
            Creep* aux = this->m_aCreep[i];
            this->m_aCreep.erase(this->m_aCreep.begin() + i);
            if(aux!=nullptr)
            {
                delete aux;
                aux = nullptr;
                --i;
                --size;
            }
        }
	}
}

void CreepList::render(sf::RenderWindow& window)
{
    int i;
	int size = this->m_aCreep.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aCreep[i]->render(window);
	}
}

