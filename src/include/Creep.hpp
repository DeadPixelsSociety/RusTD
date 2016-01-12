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
#ifndef CREEP_H
#define CREEP_H

#include "TCreep.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../include/Animation.hpp"

#define CREEP_SELECTION_RADIUS 25

class Projectile;
class ProjectileList;

enum class CreepState
{
	Normal,
	Dead,
	Leaked
};

class Creep
{
public:
	Creep(void);
	Creep(TCreep* tc);
	Creep(TCreep* tc, unsigned int rank);

	~Creep(void);

    TCreep* getTCreep(void);
    sf::Vector2f getPosition(void);
    CreepState getState(void);
    float getCurrentHealth(void);

    void setPath(std::vector<sf::Vector2i>& path);
    void setState(CreepState state);
    void setHoverIndicatorEnabled(bool e);

    void addProjectile(Projectile* proj);
    void removeProjectile(Projectile* proj);

    bool isChasedByProjectile(void);

    void takeDamage(float damage);

    bool collide(sf::Vector2f position);

	void update(float dt);
    void renderCreep(sf::RenderWindow& window);
    void renderDialog(sf::RenderWindow& window);

protected:
	TCreep* m_tcreep;
	float m_maximal_health, m_current_health;
	sf::Vector2f m_position;
    std::vector<sf::Vector2i> m_path;//?
    ProjectileList* m_aProjectile;
    unsigned int m_path_point_index;
    CreepState m_state;
    sf::Sprite* m_sprite;
    Animation* m_animation;
	float m_rand_dead;
	sf::Vector2f m_next_point;
	bool m_hover_indicator;
	unsigned int m_rank;
};

#endif
