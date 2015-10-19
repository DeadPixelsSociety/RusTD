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
#include "../include/Map.hpp"
#include "../include/Random.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"
#include "../include/config.hpp"

/*explicit*/ Map::Map(uint32_t width, uint32_t height)
: m_texture(nullptr)
, m_image(nullptr)
, m_textures(nullptr)
, m_width(width)
, m_height(height)
{
	this->generateBackground();
}

/*explicit*/ Map::Map(uint32_t width, uint32_t height, const std::vector<sf::Vector2i>& path)
: m_texture(nullptr)
, m_image(nullptr)
, m_textures(nullptr)
, m_width(width)
, m_height(height)
{
	this->generateBackground();
	generatePath(path);
}

/*virtual*/ Map::~Map()
{
	if(nullptr != m_texture)
	{
		delete m_texture;
	}
	if(nullptr != m_image)
	{
		delete m_image;
	}
	if(nullptr != m_textures)
	{
		delete m_textures;
	}
}

/*virtual*/ void Map::generateBackground()
{
	// Building data
	m_background.clear();
	for(uint32_t i = 0; i < m_width; ++i)
	{
		m_background.push_back(std::vector<int>());
		for(uint32_t j = 0; j < m_height; ++j)
		{
			int tile = Random::NextInt(0, 1000);
			if(tile<850)tile=TILE0;
			else if(tile<925)tile=TILE1;
			else if(tile<975)tile=TILE2;
			else if(tile<995)tile=TILE3;
			else tile=TILE4;
			if(tile < TILE3)
				tile += Random::NextInt(0, 3) * 0x10;
			m_background[i].push_back(tile);
		}
	}
	// Creating image
	if(nullptr != m_image)
	{
		delete m_image;
	}
	m_image = new sf::Image();
	m_image->create(GRID_UNIT * m_width, GRID_UNIT * m_height, sf::Color::Transparent);
	// Create textures
	if(nullptr == m_textures)
	{
		sf::Image textures = ResourceManager::Instance()->getTexture("Static Ground Textures")->copyToImage();
		m_textures = new sf::Image();
		m_textures->create(GRID_UNIT * 5, GRID_UNIT * 4, sf::Color::Transparent);
		sf::Image currentImage;
		sf::Texture tmp;
		for(int i = 0; i < 5; ++i)
		{
			tmp.loadFromImage(textures, sf::IntRect(i * GRID_UNIT, 0, GRID_UNIT, GRID_UNIT));
			currentImage = tmp.copyToImage();
			m_textures->copy(currentImage, i * GRID_UNIT, 0, sf::IntRect(0, 0, GRID_UNIT, GRID_UNIT));
			for(int j = 1; j < 4; ++j)
			{
				flipTile(currentImage, 1);
				m_textures->copy(currentImage, i * GRID_UNIT, j * GRID_UNIT, sf::IntRect(0, 0, GRID_UNIT, GRID_UNIT));
			}
		}
	}
	drawBackground();
}

/*virtual*/ void Map::generateBackground(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	generateBackground();
}

/*virtual*/ void Map::generatePath(const std::vector<sf::Vector2i>& path)
{
	if(path.size() <= 1 || nullptr == m_texture)
	{
		return;
	}
	drawBackground();
	sf::Image texture = ResourceManager::Instance()->getTexture("Static Road")->copyToImage();
	sf::Image background = m_texture->copyToImage();
	int loopEnd = path.size() - 1;
	for(int i = 0; i < loopEnd; ++i)
	{
		sf::Vector2f currentPoint = getConvertedPosition(path[i]);
		sf::Vector2f nextPoint = getConvertedPosition(path[i + 1]);
		int count = getDistanceBetweenPoints(currentPoint, nextPoint) / (GRID_UNIT / 2);
		sf::Vector2f director = sf::Vector2f((nextPoint.x - currentPoint.x) / count, (nextPoint.y - currentPoint.y) / count);
		for(int j = 0; j < count; ++j)
		{
			if(currentPoint.x > 0.f && currentPoint.y > 0.f)
			{
				flipTile(texture, Random::NextInt(0, 3));
				background.copy(texture, currentPoint.x, currentPoint.y, sf::IntRect(0, 0, GRID_UNIT, GRID_UNIT), true);
			}
			currentPoint += director;
		}
	}
	sf::Vector2f last_point = getConvertedPosition(path[loopEnd]);
	if(last_point.x > 0.f && last_point.y > 0.f)
	{
		background.copy(texture, last_point.x, last_point.y, sf::IntRect(0, 0, GRID_UNIT, GRID_UNIT), true);
	}
	m_texture->loadFromImage(background, sf::IntRect(0, 0, m_width * GRID_UNIT, m_height * GRID_UNIT));
}

/*virtual*/ void Map::generate(uint32_t width, uint32_t height, const std::vector<sf::Vector2i>& path)
{
	generateBackground(width, height);
	generatePath(path);
}

/*virtual*/ void Map::generate(const std::vector<sf::Vector2i>& path)
{
	generateBackground(m_width, m_height);
	generatePath(path);
}

/*virtual*/ sf::Texture* Map::getTexture()
{
	return m_texture;
}

/*virtual*/ void Map::drawBackground()
{
	if(nullptr == m_textures)
	{
		generateBackground();
		return;
	}
	if(nullptr != m_texture)
	{
		delete m_texture;
	}
	m_texture = new sf::Texture();
	sf::Image img;
	img.create(GRID_UNIT * m_width, GRID_UNIT * m_height, sf::Color::Transparent);
	for(uint32_t i = 0; i < m_width; ++i)
	{
		for(uint32_t j = 0; j < m_height; ++j)
		{
			img.copy(*m_textures, i * GRID_UNIT, j * GRID_UNIT, sf::IntRect(GRID_UNIT * (m_background[i][j] & 0xf), GRID_UNIT * (m_background[i][j] >> 0x4), GRID_UNIT, GRID_UNIT));
		}
	}
	m_texture->loadFromImage(img, sf::IntRect(0, 0, m_width * GRID_UNIT, m_height * GRID_UNIT));
}

/*virtual*/ void Map::flipTile(sf::Image& tile, int rotationIndex)
{
	if(rotationIndex == 0)
	{
		return;
	}
	sf::Color flipping[4];
	for(int i = 0; i < GRID_UNIT / 2; ++i)
	{
		for(int j = 0; j < GRID_UNIT / 2; ++j)
		{
			int a = GRID_UNIT - 1 - i, b = GRID_UNIT - 1 - j;
			flipping[0] = tile.getPixel(i, j);
			flipping[1] = tile.getPixel(b, i);
			flipping[2] = tile.getPixel(a, b);
			flipping[3] = tile.getPixel(j, a);
			switch(rotationIndex)
			{
			case 1:
				tile.setPixel(i, j, flipping[3]);
				tile.setPixel(b, i, flipping[0]);
				tile.setPixel(a, b, flipping[1]);
				tile.setPixel(j, a, flipping[2]);
				break;
			case 2:
				tile.setPixel(i, j, flipping[2]);
				tile.setPixel(b, i, flipping[3]);
				tile.setPixel(a, b, flipping[0]);
				tile.setPixel(j, a, flipping[1]);
				break;
			case 3:
				tile.setPixel(i, j, flipping[1]);
				tile.setPixel(b, i, flipping[2]);
				tile.setPixel(a, b, flipping[3]);
				tile.setPixel(j, a, flipping[0]);
				break;
			default:
				break;
			}
		}
	}
}
