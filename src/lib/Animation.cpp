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
#include "../include/Animation.hpp"

/*explicit*/ Animation::Animation(int id, const std::string& name, sf::Sprite* sprite, sf::IntRect first, int count, int frameMs)
: m_id(id)
, m_name(name)
, m_sprite(sprite)
, m_count(count)
, m_index(0)
, m_rect(first)
, m_state(ANIM_PLAY)
, m_frameTime(frameMs)
, m_timeSum(0.f)
, m_originalRect(first)
{}

void Animation::setSprite(sf::Sprite* sprite)
{
	m_sprite = sprite;
}

void Animation::update(float deltaTimeInSeconds)
{
	m_timeSum += (deltaTimeInSeconds * 1000);
	if(ANIM_PLAY == m_state)
	{
		if(m_timeSum >= m_frameTime)
		{
			m_timeSum = 0.f;
			m_index = (m_index+1)%m_count;
		}
	}
	else
	{
		m_timeSum = 0.f;
	}
	m_rect.left = m_rect.width * m_index;
	if(nullptr != m_sprite)
	{
		m_sprite->setTextureRect(m_rect);
	}
}

void Animation::play()
{
	m_state = ANIM_PLAY;
	m_rect.left = m_rect.width * m_index;
	if(nullptr != m_sprite)
	{
		m_sprite->setTextureRect(m_rect);
	}
}

void Animation::stop()
{
	m_state = ANIM_STOP;
	m_index = 0;
}

void Animation::pause()
{
	m_state = ANIM_STOP;
}

int Animation::getId() const
{
	return m_id;
}

std::string Animation::getName() const
{
	return m_name;
}


sf::IntRect Animation::getCurrentRect() const
{
	return m_rect;
}

sf::IntRect Animation::getOriginalRect() const
{
	return m_originalRect;
}

float Animation::getFrameTime() const
{
	return m_frameTime;
}

int Animation::getFrameCount() const
{
	return m_count;
}


