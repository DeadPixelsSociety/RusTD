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
#include "../include/GameStatePlaying.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/GameStateUI.hpp"
#include "../include/TDoodad.hpp"

/*explicit*/ GameStatePlaying::GameStatePlaying()
: GameState()
, m_map(nullptr)
, m_ui(nullptr)
{
    this->m_cl = new CreepList();
    this->m_pl = new ProjectileList();
    this->m_tl = new TowerList();
    this->m_path.push_back(sf::Vector2i(2,-1));
    this->m_path.push_back(sf::Vector2i(2,2));
    this->m_path.push_back(sf::Vector2i(5,2));
    this->m_path.push_back(sf::Vector2i(5,5));
    this->m_path.push_back(sf::Vector2i(10,5));
    this->m_path.push_back(sf::Vector2i(10,2));
    this->m_path.push_back(sf::Vector2i(7,2));
    this->m_path.push_back(sf::Vector2i(7,12));
//
    this->t_creep_spawn_cd = 100000.f;

    TTower* tt2 = TDoodad::getTTower(5);
    TTower* tt3 = TDoodad::getTTower(6);

    m_towers.push_back(new Tower(tt2, sf::Vector2i(10,8)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt2, sf::Vector2i(1,1)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt2, sf::Vector2i(0,0)));
    this->addTower(m_towers.back());
    m_towers.push_back(new Tower(tt3, sf::Vector2i(5,6)));
    this->addTower(m_towers.back());
    m_map = new Map(40, 30, this->m_path);
    for(int i = 0; i < 16; ++i)
	{
		this->m_zoomCoefs.push_back(0.5f + 0.1f * i);
	}
    this->m_currentZoom = this->m_zoomCoefs.size() - 1;
	m_view.setSize(1280 * m_zoomCoefs[m_currentZoom], 900 * m_zoomCoefs[m_currentZoom]);
	m_view.setCenter(640 * m_zoomCoefs[m_currentZoom], 450 * m_zoomCoefs[m_currentZoom]);
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 1280.f / 1600.f, 1.f));
	m_view.setRotation(0.0f);
}

/*virtual*/ GameStatePlaying::~GameStatePlaying()
{
	for(std::vector<Tower*>::iterator it = m_towers.begin(); it != m_towers.end(); ++it)
	{
		delete *it;
	}
	delete m_map;
}

void GameStatePlaying::addCreep(Creep* cre)
{
    cre->setPath(this->m_path);
    this->m_cl->addCreep(cre);
}

void GameStatePlaying::addTower(Tower* tow)
{
    this->m_tl->addTower(tow);
}

/*virtual*/ void GameStatePlaying::update(float dt)
{
	if(nullptr == m_ui) // m_ui is not push in constructor, because this state is not already pushed when constructed
	{
		m_ui = new GameStateUI(this);
		GameStateManager::Instance()->pushState(m_ui, true, true, true);
	}

    this->m_tl->attackList(this->m_pl,this->m_cl);

    this->t_creep_spawn_cd += dt;
    if(this->t_creep_spawn_cd>=1.5f)
    {
        TCreep* tc = TDoodad::getTCreep(0);

        Creep* new_c = new Creep(tc);
        this->addCreep(new_c);
        this->t_creep_spawn_cd = 0.f;
    }

    this->m_cl->update(dt);
    this->m_tl->update(dt);
    this->m_pl->update(dt);

	// Check if mouse is on sides and scroll if yes
	sf::RenderWindow* window = GameStateManager::Instance()->getWindow();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2u windowSize = window->getSize();
	float minX = windowSize.x * SCROLL_PERCENT;
	float maxX = (windowSize.x * WIDTH_VIEWPORT_COEF) - minX;
	float minY = windowSize.y * SCROLL_PERCENT;
	float maxY = windowSize.y - minY;
	if(	mousePosition.x >= 0 &&
		mousePosition.y >= 0 &&
		mousePosition.x <= ((int)windowSize.x * WIDTH_VIEWPORT_COEF) &&
		mousePosition.y <= (int)windowSize.y)
	{
		sf::Vector2f center = m_view.getCenter();
		if(mousePosition.x < minX)
		{
			center.x -= SCROLL_MAX_SPEED * dt * (minX - mousePosition.x) / minX;
		}
		else if(mousePosition.x > maxX)
		{
			center.x -= SCROLL_MAX_SPEED * dt * (maxX - mousePosition.x) / minX;
		}
		if(mousePosition.y < minY)
		{
			center.y -= SCROLL_MAX_SPEED * dt * (minY - mousePosition.y) / minY;
		}
		else if(mousePosition.y > maxY)
		{
			center.y -= SCROLL_MAX_SPEED * dt * (maxY - mousePosition.y) / minY;
		}
		sf::Vector2f limit_world((LEVEL_WIDTH / 4.f) * m_zoomCoefs[m_currentZoom], (LEVEL_HEIGHT / 4.f) * m_zoomCoefs[m_currentZoom]);

		// Check if center do not show empty spaces
		center.x = MAX(center.x, limit_world.x);
		center.x = MIN(center.x, LEVEL_WIDTH - limit_world.x);
		center.y = MAX(center.y, limit_world.y);
		center.y = MIN(center.y, LEVEL_HEIGHT - limit_world.y);
		m_view.setCenter(center);
	}
}

/*virtual*/ void GameStatePlaying::render(sf::RenderWindow& window)
{
	sf::View oldView = window.getView();
	window.setView(m_view);
	window.draw(sf::Sprite(*(this->m_map->getTexture())));
	this->m_cl->render(window);
    this->m_tl->render(window);
    this->m_pl->render(window);
    window.setView(oldView);
}

/*virtual*/ void GameStatePlaying::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseMove(int positionX, int positionY)
{

}

/*virtual*/ void GameStatePlaying::mouseWheel(int delta, int positionX, int positionY)
{
	int notChanged = m_currentZoom;
	sf::Vector2u winSize = GameStateManager::Instance()->getWindow()->getSize();
	if(positionX < 0 || positionX > WIDTH_VIEWPORT_COEF * (int)winSize.x || positionY < 0 || positionY > (int)winSize.y)
	{
		return;
	}
	m_currentZoom -= delta;
	if(m_currentZoom < 0)
	{
		m_currentZoom = 0;
	}
	if((uint32_t)m_currentZoom >= m_zoomCoefs.size())
	{
		m_currentZoom = m_zoomCoefs.size() - 1;
	}
	if(m_currentZoom == notChanged)
	{
		return;
	}
	sf::RenderWindow* window = GameStateManager::Instance()->getWindow();

	// Get mouse position in world coordinates
	sf::Vector2f worldPosition = window->mapPixelToCoords(sf::Vector2i(positionX, positionY), m_view);

	// Calculate screen delta between screen center and mouse position. This delta must be the same when zoom is applied
	sf::Vector2i deltaPos(window->getSize().x * WIDTH_VIEWPORT_COEF / 2.f - positionX, window->getSize().y / 2.f - positionY);
	sf::Vector2f deltaInWorld = m_view.getCenter() - worldPosition;
	float deltaCoef = m_zoomCoefs[m_currentZoom] / m_zoomCoefs[notChanged];

	// Calculate new center position
	sf::Vector2f pos_world(worldPosition.x + deltaInWorld.x * deltaCoef, worldPosition.y + deltaInWorld.y * deltaCoef);
	sf::Vector2f limit_world((LEVEL_WIDTH / 4.f) * m_zoomCoefs[m_currentZoom], (LEVEL_HEIGHT / 4.f) * m_zoomCoefs[m_currentZoom]);

	// Check if center do not show empty spaces
	pos_world.x = MAX(pos_world.x, limit_world.x);
	pos_world.x = MIN(pos_world.x, LEVEL_WIDTH - limit_world.x);
	pos_world.y = MAX(pos_world.y, limit_world.y);
	pos_world.y = MIN(pos_world.y, LEVEL_HEIGHT - limit_world.y);

	// Set new view size
	m_view.setSize((LEVEL_WIDTH / 2.f) * m_zoomCoefs[m_currentZoom], (LEVEL_HEIGHT / 2.f) * m_zoomCoefs[m_currentZoom]);
	m_view.setCenter(pos_world);
}

/*virtual*/ void GameStatePlaying::keyDown(sf::Keyboard::Key key)
{

}

/*virtual*/ void GameStatePlaying::keyUp(sf::Keyboard::Key key)
{
	if(key == sf::Keyboard::Escape)
	{
		GameStateManager::Instance()->popState(); // Pop GameStateUI
		GameStateManager::Instance()->popState(); // Pop GameStatePlaying
	}
}
