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
