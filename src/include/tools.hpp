#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define VIEW_WIDTH 1600
#define VIEW_HEIGHT 900

#define _PI 3.14159265359
#define DEG_TO_RAD(x) ((x) * _PI / 180.f)
#define RAD_TO_DEG(x) ((x) * 180.f / _PI)

float getDistanceBetweenPoints(sf::Vector2f p1,sf::Vector2f p2);

void resizeWindow(sf::RenderWindow& window, unsigned int width, unsigned int height);

void switchFullScreen(sf::RenderWindow* pWindow, bool fullscreen);

sf::Vector2f getWindowCenterInWorld(sf::RenderWindow& window);

float getLookingAngle(const sf::Vector2f& v);

sf::Vector2f getConvertedPosition(sf::Vector2i);

#endif // TOOLS_HPP
