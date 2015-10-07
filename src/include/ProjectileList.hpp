#ifndef PROJECTILE_LIST_H
#define PROJECTILE_LIST_H

#include <vector>

#include "Projectile.hpp"

class ProjectileList
{
public:
	ProjectileList(void);

	~ProjectileList(void);

    bool isEmpty(void);

    void addProjectile(Projectile* proj);
    void removeProjectile(Projectile* proj);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	std::vector<Projectile*> m_aProjectile;

};

#endif
