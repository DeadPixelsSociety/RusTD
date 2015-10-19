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
#include "../include/Window.hpp"

/*static*/ std::vector<sf::VideoMode> Window::availableVideoModes;
/*static*/ sf::VideoMode Window::windowedVideoMode;
/*static*/ int Window::selectedFullScreenVideoMode;
/*static*/ bool Window::isFullScreen;

/*static*/ void Window::Initialize()
{
	Window::availableVideoModes = sf::VideoMode::getFullscreenModes();
	Window::windowedVideoMode = sf::VideoMode(1200, 675, 32);
	Window::selectedFullScreenVideoMode = 0;
	Window::isFullScreen = false;
}

/*explicit*/ Window::Window(){}
/*virtual*/ Window::~Window(){}
