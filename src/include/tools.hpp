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
#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <string>

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

std::vector<std::string> splitString(const std::string& str, char separator);

#endif // TOOLS_HPP
