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

