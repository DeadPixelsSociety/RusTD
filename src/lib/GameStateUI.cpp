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
#include "../include/GameStateUI.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"
#include "../include/TDoodad.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

/*explicit*/ GameStateUI::GameStateUI(GameStatePlaying* gsp)
: GameState()
, m_gsp(gsp)
, m_panel(nullptr)
, m_tt(nullptr)
{
	m_panel = new sf::Sprite();
	m_panel->setTexture(*(ResourceManager::Instance()->getTexture("Static Panel Ui")));
	m_panel->setPosition(0.0f, 0.0f);

    std::vector<int> ids = TDoodad::getTTowerIds();
    int i=0;
    for(std::vector<int>::iterator it=ids.begin() ; it!=ids.end() ; ++it)
    {
        TTower* tt = TDoodad::getTTower(*it);
        this->m_tt = tt;
        Button* button = new Button(ResourceManager::Instance()->getTexture("Static Gear"),"",*(ResourceManager::Instance()->getFont("Global Font")),1);
        button->setPosition(sf::Vector2f(1400.f,i*64.f));
        this->m_aButtonTTower.push_back(std::pair<Button*,TTower*>(button,tt));
        i++;
    }

	this->m_leaks_text = new sf::Text();
    this->m_leaks_text->setFont(*(ResourceManager::Instance()->getFont("Global Font")));
	this->m_leaks_text->setString("Leaks");
    this->m_leaks_text->setCharacterSize(24);
    this->m_leaks_text->setPosition(100.f,800.f);
}

/*virtual*/ GameStateUI::~GameStateUI()
{
	delete m_panel;
}

TTower* GameStateUI::getTTower(void)
{
    return this->m_tt;
}

void GameStateUI::setTTower(TTower* tt)
{
    this->m_tt = tt;
}


/*virtual*/ void GameStateUI::update(float deltaTimeInSeconds)
{
	char s[100];
	sprintf(s,"Leaks : %d",this->m_gsp->getLeak());
	this->m_leaks_text->setString(s);
}

/*virtual*/ void GameStateUI::render(sf::RenderWindow& window)
{
	window.draw(*m_panel);
	window.draw(*(this->m_leaks_text));
	unsigned int size = this->m_aButtonTTower.size();
	for(unsigned int i=0 ; i<size ; i++) {
        this->m_aButtonTTower[i].first->render(window);
        sf::Text text = sf::Text();
        text.setFont(*(ResourceManager::Instance()->getFont("Global Font")));
        text.setString(this->m_aButtonTTower[i].second->getName());
        text.setCharacterSize(16);
        sf::Vector2f button_position = this->m_aButtonTTower[i].first->getShape()->getPosition();
        text.setPosition(button_position.x+50.f,button_position.y);
        window.draw(text);
	}
}

/*virtual*/ void GameStateUI::mouseDown(sf::Mouse::Button button, int positionX, int positionY)
{
	// @TODO : check if a tower is selected
	//m_gsp->SetState(PlacingTower);
}

/*virtual*/ void GameStateUI::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
    if(button == sf::Mouse::Left)
	{
	    unsigned int size = this->m_aButtonTTower.size();
		for(unsigned int i=0; i<size ; i++)
		{
			if(this->m_aButtonTTower[i].first->isInButton(positionX, positionY))
			{
			    this->m_tt = this->m_aButtonTTower[i].second;
			    this->m_gsp->SetState(PlayingState::PlacingTower);
				return;
			}
		}
	}
}

/*virtual*/ void GameStateUI::mouseMove(int positionX, int positionY) {}

/*virtual*/ void GameStateUI::mouseWheel(int delta, int positionX, int positionY) {}

/*virtual*/ void GameStateUI::keyDown(sf::Keyboard::Key key) {}

/*virtual*/ void GameStateUI::keyUp(sf::Keyboard::Key key) {}

void GameStateUI::setSelectedTTower(TTower* tt)
{
    this->m_tt = tt;
}

