#include <cmath>

#include "../include/tools.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

float getDistanceBetweenPoints(sf::Vector2f p1,sf::Vector2f p2)
{
    float distance_x = p2.x - p1.x;
    float distance_y = p2.y - p1.y;
    float distance = sqrt(pow(distance_x,2) + pow(distance_y,2));
    return distance;
}

void resizeWindow(sf::RenderWindow& window, unsigned int width, unsigned int height)
{
	float ratioWH = (float)width/(float)height;
	constexpr float stdratio = 16.f/9.f;
	sf::View v = window.getView();
	v.setSize(1366, 768);
	v.setCenter(683, 384);
	if(ratioWH > stdratio) // Width too big
	{
		float tmp = (width - height * stdratio) / width;
		v.setViewport(sf::FloatRect(tmp / 2, 0.f, 1.f - tmp, 1.f));
	}
	else // Height too big
	{
		float tmp = (height - width / stdratio) / height;
		v.setViewport(sf::FloatRect(0.f, tmp / 2, 1.f, 1.f - tmp));
	}
	window.setView(v);
}
