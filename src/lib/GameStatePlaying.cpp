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
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"

/*explicit*/ GameStatePlaying::GameStatePlaying()
: GameState()
, m_map(nullptr)
, m_ui(nullptr)
, m_state(PlayingState::Normal)
, m_placementValid(true)
, m_selected_tower(nullptr)
, m_hovered_creep(nullptr)
, m_current_creep_wave(nullptr)
, m_leaks(0)
, m_maj_pressed(false)
, m_creep_spawn_cd(CREEP_SPAWN_PERIOD)
, m_creep_wave_cd(CREEP_WAVE_PERIOD)
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

    //TTower* tt2 = TDoodad::getTTower(5);
    //TTower* tt3 = TDoodad::getTTower(7);

    //m_towers.push_back(new Tower(tt2, sf::Vector2i(10,8)));
    //this->addTower(m_towers.back());
    //this->addTower(new Tower(tt3, sf::Vector2i(1,1)));
    //this->addTower(new Tower(tt3, sf::Vector2i(0,0)));
    //this->addTower(new Tower(tt3, sf::Vector2i(5,6)));
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
	m_placeTower = new sf::Sprite();
	m_placeTower->setTexture(*(ResourceManager::Instance()->getTexture("Static Tower Position")));

	//TCreep* tc = TDoodad::getTCreep(0);
	//this->m_current_creep_wave = new CreepWave(tc,2,0);
	this->m_current_creep_wave = nullptr;
}

/*virtual*/ GameStatePlaying::~GameStatePlaying()
{
    delete this->m_cl;
    delete this->m_pl;
	delete this->m_tl;
	delete this->m_map;
	delete this->m_placeTower;
}

int GameStatePlaying::getLeak(void)
{
	return this->m_leaks;
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

    if(this->m_current_creep_wave!=nullptr)
	{
		if(this->m_current_creep_wave->isCreepRemaining())
		{
			this->m_creep_spawn_cd += dt;
			if(this->m_creep_spawn_cd>=CREEP_SPAWN_PERIOD)
			{
				Creep* new_c = new Creep(this->m_current_creep_wave->getTCreep(),this->m_current_creep_wave->getCreepRank());
				this->addCreep(new_c);
				this->m_current_creep_wave->decrementCreepAmount();
				this->m_creep_spawn_cd = 0.f;
			}
		}
		else
		{
			delete this->m_current_creep_wave;
			this->m_current_creep_wave = nullptr;
			this->m_creep_wave_cd = 0.f;
		}
    }
    else
	{
		this->m_creep_wave_cd += dt;
		if(this->m_creep_wave_cd>=CREEP_WAVE_PERIOD)
		{
			TCreep* tc = TDoodad::getTCreep(0);
			this->m_creep_spawn_cd = CREEP_SPAWN_PERIOD;
			this->m_current_creep_wave = new CreepWave(tc,4,Random::NextInt(0,4));
		}
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
    this->isPlacementAvailable();
    this->creepLeak();
}

/*virtual*/ void GameStatePlaying::render(sf::RenderWindow& window)
{
	sf::View oldView = window.getView();
	window.setView(m_view);
	window.draw(sf::Sprite(*(this->m_map->getTexture())));
	this->m_cl->renderCreep(window);
    this->m_tl->render(window);
    this->m_pl->render(window);
	this->m_cl->renderDialog(window);
    // Draw placing mark
    if(m_state == PlayingState::PlacingTower)
	{
		window.draw(*m_placeTower);
	}
    window.setView(oldView);
}

/*virtual*/ void GameStatePlaying::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{}

/*virtual*/ void GameStatePlaying::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
	if(button == sf::Mouse::Left)
	{
	    switch(this->m_state)
	    {
            case PlayingState::Normal:
                this->m_selected_tower = this->m_tl->findTowerAtPosition(sf::Vector2i((int)m_placementPosition.x/GRID_UNIT,(int)m_placementPosition.y/GRID_UNIT));
                if(this->m_selected_tower!=nullptr)
                {
                    this->m_selected_tower->enableRangeIndicator(true);
                    this->SetState(PlayingState::TowerSelected);
                }
                break;

            case PlayingState::PlacingTower:
                if(m_placementValid)
                {
                    sf::Vector2i pos = sf::Vector2i((int)m_placementPosition.x/GRID_UNIT,(int)m_placementPosition.y/GRID_UNIT);
                    Tower* new_tower = new Tower(m_ui->getTTower(),pos);
                    this->addTower(new_tower);
                    if(!this->m_maj_pressed)
					{
						this->SetState(PlayingState::Normal);
					}
                }
                break;

            case PlayingState::TowerSelected:
                this->m_selected_tower->enableRangeIndicator(false);
                this->m_selected_tower = nullptr;
                this->SetState(PlayingState::Normal);

                this->m_selected_tower = this->m_tl->findTowerAtPosition(sf::Vector2i((int)m_placementPosition.x/GRID_UNIT,(int)m_placementPosition.y/GRID_UNIT));
                if(this->m_selected_tower!=nullptr)
                {
                    this->m_selected_tower->enableRangeIndicator(true);
                    this->SetState(PlayingState::TowerSelected);
                }
                break;

            default: break;
	    }
	}

	if(button == sf::Mouse::Right)
	{
	    switch(this->m_state)
	    {
            case PlayingState::PlacingTower:
                this->SetState(PlayingState::Normal);
                break;

            case PlayingState::TowerSelected:
                if(this->m_hovered_creep!=nullptr && this->m_selected_tower!=nullptr)
                {
                    if(this->m_selected_tower->canAttack(this->m_hovered_creep))
                    {
                        this->m_selected_tower->setTarget(this->m_hovered_creep);
                    }
                }
                break;

            default: break;
	    }
	}
}

/*virtual*/ void GameStatePlaying::mouseMove(int positionX, int positionY)
{
	computeMousePosition(positionX, positionY);
	if(this->m_hovered_creep!=nullptr)
    {
        this->m_hovered_creep->setHoverIndicatorEnabled(false);
    }
	this->m_hovered_creep = this->m_cl->findCreepAtPosition(this->m_placementPosition);
    if(this->m_hovered_creep!=nullptr)
    {
        this->m_hovered_creep->setHoverIndicatorEnabled(true);
    }
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
	if(key == sf::Keyboard::LShift)
	{
        this->m_maj_pressed = true;
	}
}

/*virtual*/ void GameStatePlaying::keyUp(sf::Keyboard::Key key)
{
	if(key == sf::Keyboard::Escape)
	{
		GameStateManager::Instance()->popState(); // Pop GameStateUI
		GameStateManager::Instance()->popState(); // Pop GameStatePlaying
	}

	if(key == sf::Keyboard::LShift)
	{
        this->m_maj_pressed = false;
	}
}

/*virtual*/ void GameStatePlaying::SetState(PlayingState state)
{
	m_state = state;
	if(state==PlayingState::Normal)
    {
        //this->m_ui->setTTower(nullptr);
    }
}

void GameStatePlaying::setCreepWave(CreepWave* cw)
{
	this->m_current_creep_wave = cw;
}


/*virtual*/ PlayingState GameStatePlaying::GetState() const
{
	return m_state;
}

void GameStatePlaying::computeMousePosition(int positionX, int positionY)
{
    if(positionX>=0 && positionX<=VIEW_WIDTH*WIDTH_VIEWPORT_COEF && positionY>=0 && positionY<VIEW_HEIGHT)
    {
        m_placementPosition = GameStateManager::Instance()->getWindow()->mapPixelToCoords(sf::Vector2i(positionX, positionY), m_view);
    }
    else
    {
        m_placementPosition = sf::Vector2f(-1.0f, -1.0f);
    }
}

void GameStatePlaying::isPlacementAvailable()
{
    if(m_state == PlayingState::PlacingTower)
	{
		if(m_placementPosition.x != -1.0f && m_placementPosition.y != -1.0f)
		{
			this->m_placementPosition.x = (int)(m_placementPosition.x / 64) * 64.f;
			this->m_placementPosition.y = (int)(m_placementPosition.y / 64) * 64.f;
			this->m_placeTower->setPosition(m_placementPosition.x, m_placementPosition.y);

			// On tower
			sf::Vector2i gridPlacementPosition = sf::Vector2i((int)m_placementPosition.x/64,(int)m_placementPosition.y/64);
			this->m_placementValid = this->m_tl->isPlacementAvailable(gridPlacementPosition);

			// On path
            if(this->m_placementValid)
            {
                int i;
                int size = this->m_path.size();
                if(size>0)
                {
                    if(gridPlacementPosition.x==this->m_path[0].x && gridPlacementPosition.y==this->m_path[0].y)
                    {
                        this->m_placementValid = false;
                    }
                    else
                    {
                        for(i=1 ; i<size ; i++)
                        {
                            int min_limit_x = MIN(this->m_path[i-1].x,this->m_path[i].x);
                            int min_limit_y = MIN(this->m_path[i-1].y,this->m_path[i].y);
                            int max_limit_x = MAX(this->m_path[i-1].x,this->m_path[i].x);
                            int max_limit_y = MAX(this->m_path[i-1].y,this->m_path[i].y);

                            if(gridPlacementPosition.x>=min_limit_x && gridPlacementPosition.x<=max_limit_x
                               && gridPlacementPosition.y>=min_limit_y && gridPlacementPosition.y<=max_limit_y)
                            {
                                this->m_placementValid = false;
                                break;
                            }
                        }
                    }
                }
            }

            // Update tower mark
			if(this->m_placementValid)
			{
				this->m_placeTower->setColor(sf::Color::Green);
			}
			else
			{
				this->m_placeTower->setColor(sf::Color::Red);
			}
		}
	}
}

void GameStatePlaying::creepLeak()
{
	int size = this->m_path.size();
	if(size>0)
	{
		this->m_leaks += this->m_cl->creepLeak(this->m_path[size-1]);
	}
}
