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

bool TowerList::isPlacementAvailable(sf::Vector2i placement)
{
    int i;
    int size = this->m_aTower.size();
    for(i=0 ; i<size ; i++)
    {
        if(!this->m_aTower[i]->isPlacementAvailable(placement))
        {
            return false;
        }
    }
    return true;
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

