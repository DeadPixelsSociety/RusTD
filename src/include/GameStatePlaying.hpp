#ifndef GAMESTATEPLAYING_HPP
#define GAMESTATEPLAYING_HPP

#include "GameState.hpp"
#include "Map.hpp"
#include "TowerList.hpp"
#include "CreepList.hpp"
#include "ProjectileList.hpp"
#include "Random.hpp"
#include <vector>

class GameStatePlaying : public GameState
{
public:

	explicit GameStatePlaying(void);
	virtual ~GameStatePlaying(void);

    void addCreep(Creep* cre);
    void addTower(Tower* tow);

	virtual void update(float dt);
	virtual void render(sf::RenderWindow& window);
	virtual void mouseDown(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);
	virtual void mouseMove(int positionX, int positionY);
	virtual void mouseWheel(int delta, int positionX, int positionY);
	virtual void keyDown(sf::Keyboard::Key key);
	virtual void keyUp(sf::Keyboard::Key key);

protected:

	CreepList* m_cl;
    ProjectileList* m_pl;
    TowerList* m_tl;
    std::vector<sf::Vector2i> m_path;
    float t_creep_spawn_cd;
	std::vector<Tower*> m_towers;
	std::vector<TTower*> m_ttowers;
	Map* m_map;

};

#endif // GAMESTATEPLAYING_HPP
