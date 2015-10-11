#include <cmath>

#include "../include/tools.hpp"
#include "../include/config.hpp"
#include "../include/GameStateManager.hpp"
#include "../include/Window.hpp"
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
	window.setSize(sf::Vector2u(width, height));
	float ratioWH = (float)width/(float)height;
	constexpr float stdratio = 16.f/9.f;
	sf::View v = window.getView();
	v.setSize(VIEW_WIDTH, VIEW_HEIGHT);
	v.setCenter(VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
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

void switchFullScreen(sf::RenderWindow* pWindow, bool fullscreen)
{
	if(Window::isFullScreen == fullscreen)
	{
		return;
	}
	Window::isFullScreen = fullscreen;
	if(pWindow)
	{
		delete pWindow;
		if(fullscreen)
		{
			pWindow = new sf::RenderWindow(Window::availableVideoModes[Window::selectedFullScreenVideoMode], GAME_TITLE, sf::Style::Fullscreen);
		}
		else
		{
			pWindow = new sf::RenderWindow(Window::windowedVideoMode, GAME_TITLE, sf::Style::Titlebar | sf::Style::Close);
		}
		resizeWindow(*pWindow, pWindow->getSize().x, pWindow->getSize().y);
		GameStateManager::Instance()->setWindow(*pWindow);
	}
}

sf::Vector2f getWindowCenterInWorld(sf::RenderWindow& window)
{
	sf::Vector2u s = window.getSize();
	return window.mapPixelToCoords(sf::Vector2i(s.x / 2, s.y / 2));
}

