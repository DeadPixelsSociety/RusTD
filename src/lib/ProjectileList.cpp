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
		if(this->m_aProjectile[i]->getState()==1)
        {
            Projectile* aux = this->m_aProjectile[i];
            this->m_aProjectile.erase(this->m_aProjectile.begin() + i);
            aux->getTarget()->removeProjectile(aux);
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

void ProjectileList::render(sf::RenderWindow& window)
{
    int i;
	int size = this->m_aProjectile.size();
	for(i=0 ; i<size ; i++)
	{
		this->m_aProjectile[i]->render(window);
	}
}

