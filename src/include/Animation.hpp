#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#define ANIM_PLAY true
#define ANIM_STOP false
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
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <string>

enum
{
	LOOK_DOWN, LOOK_LEFT, LOOK_RIGHT, LOOK_UP
};

class Animation
{
public:

	explicit Animation(int id, const std::string& name, sf::Sprite* sprite, sf::IntRect first, int count, int frameMs);
	void setSprite(sf::Sprite* sprite);
	void update(float deltaTimeInMs);
	void play(void);
	void stop(void);
	void pause(void);
	int getId(void) const;
	std::string getName(void) const;
	sf::IntRect getCurrentRect(void) const;
	sf::IntRect getOriginalRect(void) const;
	float getFrameTime(void) const;
	int getFrameCount(void) const;
	sf::Sprite* getSprite(void) const;

protected:

	int m_id;
	std::string m_name;
	sf::Sprite* m_sprite;
	int m_count;
	int m_index;
	sf::IntRect m_rect;
	bool m_state;
	float m_frameTime;
	float m_timeSum;
	sf::IntRect m_originalRect;
};

#endif // ANIMATION_HPP
