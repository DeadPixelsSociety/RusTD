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
#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

enum
{
	TILE0 		= 0x00,
	TILE1 		= 0x01,
	TILE2 		= 0x02,
	TILE3 		= 0x03,
	TILE4		= 0x04,
	ROTATE0 	= 0x00,
	ROTATE90 	= 0x10,
	ROTATE180 	= 0x20,
	ROTATE270 	= 0x30,
};

class Map
{
public:

	explicit Map(uint32_t width, uint32_t height);
	explicit Map(uint32_t width, uint32_t height, const std::vector<sf::Vector2i>& path);
	virtual ~Map(void);

	virtual void generateBackground(void);
	virtual void generateBackground(uint32_t width, uint32_t height);
	virtual void generatePath(const std::vector<sf::Vector2i>& path);
	virtual void generate(uint32_t width, uint32_t height, const std::vector<sf::Vector2i>& path);
	virtual void generate(const std::vector<sf::Vector2i>& path);
	virtual sf::Texture* getTexture(void);

protected:

	virtual void drawBackground(void);
	virtual void flipTile(sf::Image& tile, int rotationIndex);

	sf::Texture* m_texture;
	std::vector<std::vector<int>> m_background;
	sf::Image* m_image;
	sf::Image* m_textures;

	uint32_t m_width;
	uint32_t m_height;

};

#endif // MAP_HPP
