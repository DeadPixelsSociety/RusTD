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
#include "../include/GameStateQuestionBox.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"
#include "../include/config.hpp"

/*explicit*/ GameStateQuestionBox::GameStateQuestionBox(std::string text, std::vector<std::string>& buttons, std::function<void(int,void*)> callbacks, void* cbData)
: GameState()
, m_text(new sf::Text(text, *(ResourceManager::Instance()->getFont("Global Font")), 30))
, m_panel(new sf::Sprite())
, m_callbacks(callbacks)
, m_cbData(cbData)
{
	// Place texture on panel
	m_panel->setTexture(*(ResourceManager::Instance()->registerTexture("data/texture/qb_panel.png", "Question Box Panel")));
	// Center the panel on the screen
	sf::Vector2f centerWorld = getWindowCenterInWorld(*(GameStateManager::Instance()->getWindow()));
	m_panel->setPosition(sf::Vector2f(centerWorld.x - m_panel->getLocalBounds().width / 2, centerWorld.y - m_panel->getLocalBounds().height / 2));
	// Color and place the text on the panel
	m_text->setColor(sf::Color::Black);
	m_text->setPosition((int)(m_panel->getPosition().x + (m_panel->getLocalBounds().width - m_text->getLocalBounds().width) / 2.f),
						(int)(m_panel->getPosition().y + (m_panel->getLocalBounds().height * 0.75f - m_text->getLocalBounds().height) / 2.f));
	// Get the Y position ofthe buttons
	float top = m_panel->getPosition().y + m_panel->getLocalBounds().height * 0.75f + 15;
	int spaces = m_panel->getLocalBounds().width - 3*QB_BUTTON_WIDTH / 4;
	int loopEnd = MIN(3, buttons.size());
	// Create buttons
	for(int i = 0; i < loopEnd; ++i)
	{
		m_buttons.push_back(new Button(QB_BUTTON_WIDTH, QB_BUTTON_HEIGHT, buttons[i], *(ResourceManager::Instance()->getFont("Global Font")), 20, sf::Color::Transparent, sf::Color::Black));
		m_buttons.back()->setPosition(sf::Vector2f(m_panel->getPosition().x + m_panel->getLocalBounds().width - spaces - (loopEnd - i) * (QB_BUTTON_WIDTH + spaces), top));
	}
}

/*explicit*/ GameStateQuestionBox::GameStateQuestionBox(std::string text, int buttonCount, const char* buttons[], std::function<void(int,void*)> callbacks, void* cbData)
: GameState()
, m_text(new sf::Text(text, *(ResourceManager::Instance()->getFont("Global Font")), 30))
, m_panel(new sf::Sprite())
, m_callbacks(callbacks)
, m_cbData(cbData)
{
	// Place texture on panel
	m_panel->setTexture(*(ResourceManager::Instance()->getTexture( "Question Box Panel")));
	// Center the panel on the screen
	sf::Vector2f centerWorld = getWindowCenterInWorld(*(GameStateManager::Instance()->getWindow()));
	m_panel->setPosition(sf::Vector2f(centerWorld.x - m_panel->getLocalBounds().width / 2, centerWorld.y - m_panel->getLocalBounds().height / 2));
	// Color and place the text on the panel
	m_text->setColor(sf::Color::Black);
	m_text->setPosition((int)(m_panel->getPosition().x + (m_panel->getLocalBounds().width - m_text->getLocalBounds().width) / 2.f),
						(int)(m_panel->getPosition().y + (m_panel->getLocalBounds().height * 0.75f - m_text->getLocalBounds().height) / 2.f));
	// Get the Y position ofthe buttons
	float top = m_panel->getPosition().y + m_panel->getLocalBounds().height * 0.75f + 15;
	int spaces = (m_panel->getLocalBounds().width - 3*QB_BUTTON_WIDTH) / 4;
	int loopEnd = MIN(3, buttonCount);
	// Create buttons
	for(int i = 0; i < loopEnd; ++i)
	{
		m_buttons.push_back(new Button(QB_BUTTON_WIDTH, QB_BUTTON_HEIGHT, buttons[i], *(ResourceManager::Instance()->getFont("Global Font")), 20, sf::Color::Transparent, sf::Color::Black));
		m_buttons.back()->setPosition(sf::Vector2f(m_panel->getPosition().x + m_panel->getLocalBounds().width - spaces - (loopEnd - i) * (QB_BUTTON_WIDTH + spaces), top));
	}
}

/*virtual*/ GameStateQuestionBox::~GameStateQuestionBox()
{
	delete m_text;
	delete m_panel;
	for(std::vector<Button*>::const_iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		delete *it;
	}
}

/*virtual*/ void GameStateQuestionBox::update(float deltaTimeInSeconds)
{}

/*virtual*/ void GameStateQuestionBox::render(sf::RenderWindow& window)
{
	window.draw(*m_panel);
	window.draw(*m_text);
	for(std::vector<Button*>::const_iterator it = m_buttons.begin(); it != m_buttons.end(); ++it)
	{
		(*it)->render(window);
	}
}

/*virtual*/ void GameStateQuestionBox::mouseUp(sf::Mouse::Button button, int positionX, int positionY)
{
	if(button == sf::Mouse::Left)
	{
		for(unsigned int i = 0; i < m_buttons.size(); ++i)
		{
			if(m_buttons[i]->isInButton(positionX, positionY))
			{
				m_callbacks(i, m_cbData);
				return;
			}
		}
	}
}

