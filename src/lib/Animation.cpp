#include "../include/Animation.hpp"

/*explicit*/ Animation::Animation(sf::Sprite* sprite, sf::IntRect first, int count, int frameMs)
: m_sprite(sprite)
, m_count(count)
, m_index(0)
, m_rect(first)
, m_state(ANIM_PLAY)
, m_frameTime(frameMs)
{
	m_clock.restart();
}

void Animation::update(void)
{
	if(ANIM_PLAY == m_state)
	{
		if(m_clock.getElapsedTime().asMilliseconds() >= m_frameTime)
		{
			m_clock.restart();
			m_index = (m_index+1)%m_count;
		}
	}
	else
	{
		m_clock.restart();
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

