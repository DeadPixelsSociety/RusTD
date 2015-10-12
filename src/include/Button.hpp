#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button
{
public:

	explicit Button(sf::Texture* texture, const std::string& text, sf::Font& font, int textSize);
	explicit Button(int width, int height, const std::string& text, sf::Font& font, int textSize, const sf::Color& color, const sf::Color& textColor);
	virtual ~Button(void);

	virtual void setColor(const sf::Color& color);
	virtual void setTextColor(const sf::Color& color);
	virtual void setText(const std::string& text);
	virtual void setTextSize(int size);
	virtual void setTextFont(sf::Font& font);
	virtual void setTexture(sf::Texture& texture);
	virtual void removeTexture(void);
	virtual void setSize(int width, int height);
	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPositionOnWindow(const sf::Vector2f& position, sf::RenderWindow& window);
	virtual int getWidth(void) const;
	virtual int getHeight(void) const;
	virtual bool isMouseInButton(sf::RenderWindow& window) const;
	virtual bool isInButton(int x, int y) const;
	virtual sf::RectangleShape* getShape(void);

	virtual void update(float deltaTimeInSeconds);
	virtual void render(sf::RenderWindow& window);

protected:

	sf::RectangleShape* m_shape;
	sf::Text* m_text;

};

#endif // BUTTON_HPP
