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
#include "../include/Button.hpp"
#include "../include/tools.hpp"
#include "../include/config.hpp"
#include "../include/GameStateManager.hpp"
#include <SFML/Window/Mouse.hpp>
#include<iostream>
/*explicit*/ Button::Button(sf::Texture* texture, const std::string& text, sf::Font& font, int textSize)
: m_shape(new sf::RectangleShape())
, m_text(new sf::Text(text, font, textSize))
{
	m_shape->setTexture(texture);
	m_shape->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	setPosition(sf::Vector2f());
}

/*explicit*/ Button::Button(int width, int height, const std::string& text, sf::Font& font, int textSize, const sf::Color& color, const sf::Color& textColor)
: m_shape(new sf::RectangleShape(sf::RectangleShape(sf::Vector2f(width, height))))
, m_text(new sf::Text(text, font, textSize))
{
	m_shape->setFillColor(color);
	m_text->setColor(textColor);
	setPosition(sf::Vector2f());
}

/*virtual*/ Button::~Button()
{
	delete m_shape;
	delete m_text;
}

/*virtual*/ void Button::setColor(const sf::Color& color)
{
	m_shape->setFillColor(color);
}

/*virtual*/ void Button::setTextColor(const sf::Color& color)
{
	m_text->setColor(color);
}

/*virtual*/ void Button::setText(const std::string& text)
{
	m_text->setString(text);
}

/*virtual*/ void Button::setTextSize(int size)
{
	m_text->setCharacterSize(size);
}

/*virtual*/ void Button::setTextFont(sf::Font& font)
{
	m_text->setFont(font);
}

/*virtual*/ void Button::setTexture(sf::Texture& texture)
{
	sf::Vector2f v = m_shape->getSize();
	m_shape->setTexture(&texture);
	m_shape->setSize(v);
}

/*virtual*/ void Button::removeTexture()
{
	m_shape->setTexture(nullptr);
}

/*virtual*/ void Button::setSize(int width, int height)
{
	m_shape->setSize(sf::Vector2f(width, height));
}

/*virtual*/ void Button::setPosition(const sf::Vector2f& position)
{
	m_shape->setPosition(sf::Vector2f((int)(position.x), (int)(position.y)));
	m_text->setPosition((int)(position.x + ((m_shape->getLocalBounds().width - m_text->getLocalBounds().width) / 2.f)),
						(int)(position.y + ((m_shape->getLocalBounds().height - m_text->getLocalBounds().height) / 2.f) - m_text->getLocalBounds().height * 0.35f));
}

/*virtual*/ void Button::setPositionOnWindow(const sf::Vector2f& position, sf::RenderWindow& window)
{
	sf::Vector2f center = window.getView().getCenter();
	sf::Vector2f size = window.getView().getSize();
	sf::Vector2f p = sf::Vector2f((int)(position.x + center.x - size.x / 2), (int)(position.y + center.y - size.y / 2));
	m_shape->setPosition(p);
	m_text->setPosition((int)(p.x + ((m_shape->getLocalBounds().width - m_text->getLocalBounds().width) / 2.f)),
						(int)(p.y + ((m_shape->getLocalBounds().height - m_text->getLocalBounds().height) / 2.f) - m_text->getLocalBounds().height * 0.35f));
}

/*virtual*/ int Button::getWidth() const
{
	return m_shape->getSize().x;
}

/*virtual*/ int Button::getHeight() const
{
	return m_shape->getSize().y;
}

/*virtual*/ bool Button::isMouseInButton(sf::RenderWindow& window) const
{
	return m_shape->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

/*virtual*/ bool Button::isInButton(int x, int y) const
{
	return m_shape->getGlobalBounds().contains(GameStateManager::Instance()->getWindow()->mapPixelToCoords(sf::Vector2i(x, y)));
}

/*virtual*/ sf::RectangleShape* Button::getShape()
{
	return m_shape;
}
/*virtual*/ sf::Text* Button::getText()
{
	return m_text;
}

/*virtual*/ void Button::update(float deltaTimeInSeconds)
{}

/*virtual*/ void Button::render(sf::RenderWindow& window)
{
	window.draw(*m_shape);
	window.draw(*m_text);
}
