#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "config.hpp"
#include "Creep.hpp"

class Projectile
{
public:
	Projectile(void);
	Projectile(float speed, float damage, Creep* target, sf::Vector2f position);

	~Projectile(void);

    sf::Vector2f getPosition(void);
    int getState(void);
    Creep* getTarget(void);

	void update(float dt);
	void render(sf::RenderWindow& window);

protected:
	float m_speed, m_damage;
	Creep* m_target;
	sf::Vector2f m_position;
    sf::Vector2i m_target_sign;
    int m_state;

};

#endif
