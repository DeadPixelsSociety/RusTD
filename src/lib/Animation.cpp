#include "../include/Animation.hpp"

/*explicit*/ Animation::Animation(sf::Sprite* sprite, sf::IntRect first, int count, int frameMs)
: m_sprite(sprite)
, m_count(count)
, m_index(0)
, m_rect(first)
, m_state(ANIM_PLAY)
, m_frameTime(frameMs)
, m_timeSum(0)
{}

void Animation::update(float deltaTimeInSeconds)
{
	m_timeSum += (int)(deltaTimeInSeconds * 1000);
	if(ANIM_PLAY == m_state)
	{
		if(m_timeSum >= m_frameTime)
		{
			m_timeSum = 0;
			m_index = (m_index+1)%m_count;
		}
	}
	else
	{
		m_timeSum = 0;
	}
	m_rect.left = m_rect.width * m_index;
	m_sprite->setTextureRect(m_rect);
}

void Animation::play()
{
	m_state = ANIM_PLAY;
	m_rect.left = m_rect.width * m_index;
	m_sprite->setTextureRect(m_rect);
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

