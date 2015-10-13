#include "../include/Map.hpp"
#include "../include/Random.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"

/*explicit*/ Map::Map(uint32_t width, uint32_t height)
: m_texture(nullptr)
, m_image(nullptr)
, m_textures(nullptr)
, m_width(width)
, m_height(height)
{
	this->generateBackground();
}

/*explicit*/ Map::Map(uint32_t width, uint32_t height, const std::vector<sf::Vector2f>& path)
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
	m_image->create(64 * m_width, 64 * m_height, sf::Color::Transparent);
	// Create textures
	if(nullptr == m_textures)
	{
		sf::Image textures = ResourceManager::Instance()->getTexture("Static Ground Textures")->copyToImage();
		m_textures = new sf::Image();
		m_textures->create(64 * 5, 64 * 4, sf::Color::Transparent);
		sf::Image currentImage;
		sf::Texture tmp;
		for(int i = 0; i < 5; ++i)
		{
			tmp.loadFromImage(textures, sf::IntRect(i * 64, 0, 64, 64));
			currentImage = tmp.copyToImage();
			m_textures->copy(currentImage, i * 64, 0, sf::IntRect(0, 0, 64, 64));
			for(int j = 1; j < 4; ++j)
			{
				flipTile(currentImage, 1);
				m_textures->copy(currentImage, i * 64, j * 64, sf::IntRect(0, 0, 64, 64));
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

/*virtual*/ void Map::generatePath(const std::vector<sf::Vector2f>& path)
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
		sf::Vector2f currentPoint = path[i];
		sf::Vector2f nextPoint = path[i + 1];
		int count = getDistanceBetweenPoints(currentPoint, nextPoint) / 32.f;
		sf::Vector2f director = sf::Vector2f((nextPoint.x - currentPoint.x) / count, (nextPoint.y - currentPoint.y) / count);
		for(int j = 0; j < count; ++j)
		{
			if(currentPoint.x > 32.f && currentPoint.y > 32.f)
			{
				flipTile(texture, Random::NextInt(0, 3));
				background.copy(texture, currentPoint.x - 32, currentPoint.y - 32, sf::IntRect(0, 0, 64, 64), true);
			}
			currentPoint += director;
		}
	}
	if(path[loopEnd].x > 32.f && path[loopEnd].y > 32.f)
	{
		background.copy(texture, path[loopEnd].x - 32, path[loopEnd].y - 32, sf::IntRect(0, 0, 64, 64), true);
	}
	m_texture->loadFromImage(background, sf::IntRect(0, 0, m_width * 64, m_height * 64));
}

/*virtual*/ void Map::generate(uint32_t width, uint32_t height, const std::vector<sf::Vector2f>& path)
{
	generateBackground(width, height);
	generatePath(path);
}

/*virtual*/ void Map::generate(const std::vector<sf::Vector2f>& path)
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
	img.create(64 * m_width, 64 * m_height, sf::Color::Transparent);
	for(uint32_t i = 0; i < m_width; ++i)
	{
		for(uint32_t j = 0; j < m_height; ++j)
		{
			img.copy(*m_textures, i * 64, j * 64, sf::IntRect(64 * (m_background[i][j] & 0xf), 64 * (m_background[i][j] >> 0x4), 64, 64));
		}
	}
	m_texture->loadFromImage(img, sf::IntRect(0, 0, m_width * 64, m_height * 64));
}

/*virtual*/ void Map::flipTile(sf::Image& tile, int rotationIndex)
{
	if(rotationIndex == 0)
	{
		return;
	}
	sf::Color flipping[4];
	for(int i = 0; i < 32; ++i)
	{
		for(int j = 0; j < 32; ++j)
		{
			int a = 63 - i, b = 63 - j;
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
