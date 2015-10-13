#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Window
{
public:
	virtual ~Window(void);

	static std::vector<sf::VideoMode> availableVideoModes;
	static sf::VideoMode windowedVideoMode;
	static int selectedFullScreenVideoMode;
	static bool isFullScreen;

	static void Initialize(void);

protected:

	explicit Window(void);

};

#endif // WINDOW_HPP
