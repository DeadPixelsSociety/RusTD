#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define VIEW_WIDTH 1600
#define VIEW_HEIGHT 900

float getDistanceBetweenPoints(sf::Vector2f p1,sf::Vector2f p2);

void resizeWindow(sf::RenderWindow& window, unsigned int width, unsigned int height);

void switchFullScreen(sf::RenderWindow* pWindow, bool fullscreen);

sf::Vector2f getWindowCenterInWorld(sf::RenderWindow& window);

#endif // TOOLS_HPP
