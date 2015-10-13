#ifndef LEVEL_H
#define LEVEL_H

#include "TowerList.hpp"
#include "CreepList.hpp"
#include "ProjectileList.hpp"
#include "Random.hpp"

class Level
{
public:
	Level(void);

	~Level(void);

    void addCreep(Creep* cre);
    void addTower(Tower* tow);

	void update(float dt);
    void render(sf::RenderWindow& window);

    std::vector<sf::Vector2f>& getPath(void);

protected:
	CreepList* m_cl;
    ProjectileList* m_pl;
    TowerList* m_tl;
    std::vector<sf::Vector2f> m_path;
    float t_creep_spawn_cd;

};

#endif
