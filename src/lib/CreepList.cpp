/*

	RusTD - A rusted Tower Defense game
    Copyright (C) 2015  Beuzmoker, Enferium, Farijo, Vizepi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "../include/CreepList.hpp"

CreepList::CreepList(void)
{}

CreepList::~CreepList(void)
{
    printf("--delete \n");
    for(std::vector<Creep*>::iterator it=this->m_aCreep.begin() ; it!=this->m_aCreep.end() ; ++it)
    {
        Creep* aux = *it;
        this->m_aCreep.erase(it);
        if(aux!=nullptr)
        {
            printf("delete \n");

            delete aux;
            aux = nullptr;
            --it;
        }
    }



/*
    int size = this->m_aCreep.size();
	for(int i=0 ; i<size ; i++)
	{
	    Creep* aux = this->m_aCreep[i];
        this->m_aCreep.erase(this->m_aCreep.begin()+i);
        if(aux!=nullptr)
        {
            printf("delete %d\n",i);
            delete aux;
            aux = nullptr;
            --i;
            --size;
        }
	}*/
}

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

void CreepList::removeCreep(Creep* cre)
{
    std::vector<Creep*>::iterator itb = this->m_aCreep.begin();
    std::vector<Creep*>::iterator ite = this->m_aCreep.end();
    std::vector<Creep*>::iterator it = std::find(itb,ite,cre);
    if(it!=ite)
    {
        this->m_aCreep.erase(it);
    }
}

int CreepList::creepLeak(sf::Vector2i pos)
{
    int leaks = 0;
	unsigned int size = this->m_aCreep.size();
	for(unsigned int i=0 ; i<size ; i++)
	{
		Creep* c = this->m_aCreep[i];
		sf::Vector2f posf = sf::Vector2f(pos.x*GRID_UNIT,pos.y*GRID_UNIT);
		sf::FloatRect rect = sf::FloatRect(posf.x,posf.y,posf.x+GRID_UNIT,posf.y+GRID_UNIT);
		if(rect.contains(c->getPosition()) && c->getState()!=CreepState::Leaked)
        {
            leaks++;
            c->setState(CreepState::Leaked);
        }
	}
	return leaks;
}

void CreepList::update(float dt)
{
	int size = this->m_aCreep.size();
	for(int i=0 ; i<size ; i++)
	{
		this->m_aCreep[i]->update(dt);
		Creep* aux = this->m_aCreep[i];
		if(aux->getState()!=CreepState::Normal && !aux->isChasedByProjectile())
        {
        	if(aux->getState()==CreepState::Leaked)
			{
				// TODO ajouter leak score
			}

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

void CreepList::renderCreep(sf::RenderWindow& window)
{
	int size = this->m_aCreep.size();
	for(int i=0 ; i<size ; i++)
	{
		if(this->m_aCreep[i]->getState()==CreepState::Leaked)
		{
			continue;
		}
		this->m_aCreep[i]->renderCreep(window);
	}
}

void CreepList::renderDialog(sf::RenderWindow& window)
{
	int size = this->m_aCreep.size();
	for(int i=0 ; i<size ; i++)
	{
		if(this->m_aCreep[i]->getState()==CreepState::Normal)
		{
			this->m_aCreep[i]->renderDialog(window);
		}
	}
}

