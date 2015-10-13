#ifndef GAMESTATEQUESTIONBOX_HPP
#define GAMESTATEQUESTIONBOX_HPP

#include "GameState.hpp"
#include "Button.hpp"
#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#define QB_BUTTON_WIDTH 150
#define QB_BUTTON_HEIGHT 50

class GameStateQuestionBox : public GameState
{
public:

	// The maximum number of buttons is 3, if the size of the array is greater than 3, the buttons are ignored
	// The callback function take the number of the pressed button (0, 1 or 2) and an arbitrary data pointer
	// The callback's data is given in cbData arguments and is given to the callback function when a button is clicked on
	explicit GameStateQuestionBox(std::string text, std::vector<std::string>& buttons, std::function<void(int,void*)> callbacks, void* cbData);
	explicit GameStateQuestionBox(std::string text, int buttonCount, const char* buttons[], std::function<void(int,void*)> callbacks, void* cbData);
	virtual ~GameStateQuestionBox(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);

	virtual void mouseUp(sf::Mouse::Button button, int positionX, int positionY);

protected:

	sf::Text* m_text;
	sf::Sprite* m_panel;
	std::vector<Button*> m_buttons;
	std::function<void(int, void*)> m_callbacks;
	void* m_cbData;

};

/**
	How to use :
	\code
	const char* buttons[] = {"Yes", "No"};
	std::function<void(int,void*)> callback =
		[] (int index, void* data) -> void
		{
			if(index == 0)
			{
				GameStateManager::Instance()->quit(); // Quit game
			}
			else
			{
				GameStateManager::Instance()->popState(); // Pop this state
			}
		};
	GameStateQuestionBox* qb = new GameStateQuestionBox("Do you really want to quit ?", 2, buttons, callback, nullptr);
	GameStateManager::Instance()->pushState(qb, false, true, false);
	\endcode
*/

#endif // GAMESTATEQUESTIONBOX_HPP
