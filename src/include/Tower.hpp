#ifndef TOWER_H
#define TOWER_H

#include "TTower.hpp"
#include "CreepList.hpp"
#include "Projectile.hpp"

const sf::Vector2f COOLDOWN_BAR_RECTANGLE = sf::Vector2f(GRID_UNIT,3.f);
const sf::Vector2f COOLDOWN_BAR_OFFSET = sf::Vector2f(0.f,0.f);

class Tower
{
public:
	Tower(void);
	Tower(TTower* tt, sf::Vector2i position);

	~Tower(void);

    bool inRange(Creep* c);
    bool canAttack(Creep* c);

	Projectile* attackList(CreepList* ac);
    Projectile* attack(Creep* c);

	void update(float dt);
    void render(sf::RenderWindow& window);

protected:
	TTower* m_ttower;
	float m_attack_cooldown, m_proj_speed;
	sf::Vector2i m_position;
	Creep* m_last_target;
	bool m_show_range;

};

#endif
