#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

float getDistanceBetweenPoints(sf::Vector2f p1,sf::Vector2f p2);

void resizeWindow(sf::RenderWindow& window, unsigned int width, unsigned int height);

#endif // TOOLS_HPP
