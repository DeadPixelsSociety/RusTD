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
#include "../include/GameState.hpp"

#include "../include/tools.hpp"

/*virtual*/ sf::View GameState::getView()
{
	return m_view;
}

/*virtual*/ void GameState::setViewPositionX(int px)
{
	sf::FloatRect vp = m_view.getViewport();
    vp.left = (px / (float)VIEW_WIDTH);
    m_view.setViewport(vp);
}

/*virtual*/ void GameState::setViewPositionY(int px)
{
	sf::FloatRect vp = m_view.getViewport();
    vp.top = (px / (float)VIEW_HEIGHT);
    m_view.setViewport(vp);
}

/*virtual*/ void GameState::setViewWidth(int px)
{
	sf::Vector2f size = m_view.getSize();
	sf::FloatRect rect = m_view.getViewport();
	sf::Vector2f center = m_view.getCenter();
    center.x = px / 2;
    size.x = px;
    rect.width = (px / (float)VIEW_WIDTH);
    m_view.setCenter(center);
    m_view.setSize(size);
    m_view.setViewport(rect);
}

/*virtual*/ void GameState::setViewHeight(int px)
{
	sf::Vector2f size = m_view.getSize();
	sf::FloatRect rect = m_view.getViewport();
	sf::Vector2f center = m_view.getCenter();
    center.y = px / 2;
    size.y = px;
    rect.height = (px / (float)VIEW_HEIGHT);
    m_view.setCenter(center);
    m_view.setSize(size);
    m_view.setViewport(rect);
}

