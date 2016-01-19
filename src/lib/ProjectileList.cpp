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
#include <algorithm>

#include "../include/ProjectileList.hpp"

ProjectileList::ProjectileList(void)
{}

ProjectileList::~ProjectileList(void)
{}

bool ProjectileList::isEmpty(void)
{
    return this->m_aProjectile.empty();
}

void ProjectileList::addProjectile(Projectile* proj)
{
    this->m_aProjectile.push_back(proj);
}

void ProjectileList::removeProjectile(Projectile* proj)
{
    std::vector<Projectile*>::iterator itb = this->m_aProjectile.begin();
    std::vector<Projectile*>::iterator ite = this->m_aProjectile.end();
    std::vector<Projectile*>::iterator it = std::find(itb,ite,proj);
    if(it!=ite)
    {
        this->m_aProjectile.erase(it);
    }
}

void ProjectileList::update(float dt)
{
	int i;
	int size = this->m_aProjectile.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aProjectile[i]->update(dt);
		if(this->m_aProjectile[i]->getState()==2)
		{
			Projectile* aux = this->m_aProjectile[i];
			this->m_aProjectile.erase(this->m_aProjectile.begin() + i);
			if(aux != nullptr)
			{
				Creep* target = aux->getTarget();
				if(nullptr != target)
				{
					target->removeProjectile(aux);
				}
				delete aux;
				aux = nullptr;
				--i;
				--size;
			}
		}
	}
}

void ProjectileList::render(sf::RenderWindow& window)
{
    int i;
	int size = this->m_aProjectile.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aProjectile[i]->render(window);
	}
}

