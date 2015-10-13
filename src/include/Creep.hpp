#ifndef CREEP_H
#define CREEP_H

#include "TCreep.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../include/Animation.hpp"

class Projectile;
class ProjectileList;

class Creep
{
public:
	Creep(void);
	Creep(TCreep* tc);

	~Creep(void);

    TCreep* getTCreep(void);
    sf::Vector2f getPosition(void);
    int getState(void);
    float getCurrentHealth(void);

    void setPath(std::vector<sf::Vector2i>& path);

    void addProjectile(Projectile* proj);
    void removeProjectile(Projectile* proj);

    bool isChasedByProjectile(void);

    void takeDamage(float damage);

	void update(float dt);
    void render(sf::RenderWindow& window);

protected:
	TCreep* m_tcreep;
	float m_current_health;
	sf::Vector2f m_position;
    std::vector<sf::Vector2i> m_path;//?
    ProjectileList* m_aProjectile;
    unsigned int m_path_point_index;
    int m_state;
    sf::Sprite* m_sprite;
    Animation* m_animation;
	float m_rand_dead;
	sf::Vector2f m_next_point;
};

#endif
