#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#define ANIM_PLAY true
#define ANIM_STOP false

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
