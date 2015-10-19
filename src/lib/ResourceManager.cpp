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
#include "../include/ResourceManager.hpp"
#include "../include/tools.hpp"

typedef std::map<std::string, sf::Texture*>::const_iterator TextureIterator;
typedef std::map<std::string, sf::Font*>::const_iterator FontIterator;
typedef std::map<std::string, MusicResource>::const_iterator MusicIterator;
typedef std::map<std::string, sf::SoundBuffer*>::const_iterator SoundIterator;

/*explicit*/ ResourceManager::ResourceManager()
{}

/*virtual*/ ResourceManager::~ResourceManager()
{
	for(TextureIterator it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		delete it->second;
	}
	for(FontIterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
	{
		delete it->second;
	}
	for(MusicIterator it = m_musics.begin(); it != m_musics.end(); ++it)
	{
		if((it->second).loadedFromMemory)
		{
			delete [] (it->second).data;
		}
		delete (it->second).music;
	}
	for(SoundIterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
	{
		delete it->second;
	}
}

/*virtual*/ sf::Texture* ResourceManager::registerTexture(const std::string& path, const std::string& name)
{
	TextureIterator it = m_textures.find(name);
	if(it == m_textures.end())
	{
		sf::Texture* data = new sf::Texture();
		data->loadFromFile(path);
		data->setSmooth(true);
		m_textures[name] = data;
		return data;
	}
	return it->second;
}

/*virtual*/ bool ResourceManager::loadTexturesFromData(Data& data, bool destroyExisting)
{
	std::vector<file_info> infos = data.getTextures();
	for(std::vector<file_info>::iterator it = infos.begin(); it != infos.end(); ++it)
	{
		std::vector<std::string> words = splitString(splitString(it->file_name, '.')[0], '_');
		std::string resultName = "";
		for(uint32_t i = 0; i < words.size(); ++i)
		{
			if(i != 0)
			{
				resultName += ' ';
			}
			if(words[i][0] >= 'a' && words[i][0] <= 'z')
			{
				words[i][0] = words[i][0] + 'A' - 'a';
			}
			resultName += words[i];
		}
		sf::Texture* data = new sf::Texture();
		data->loadFromMemory(it->data, it->file_size);
		data->setSmooth(true);
		m_textures[resultName] = data;
	}
	return true;
}

/*virtual*/ sf::Texture* ResourceManager::getTexture(const std::string& name) const
{
	TextureIterator it = m_textures.find(name);
	if(it == m_textures.end())
	{
		return nullptr;
	}
	return it->second;
}

/*virtual*/ void ResourceManager::releaseTexture(const std::string& name)
{
	TextureIterator it = m_textures.find(name);
	if(it != m_textures.end())
	{
		delete it->second;
		m_textures.erase(it);
	}
}

/*virtual*/ sf::Font* ResourceManager::registerFont(const std::string& path, const std::string& name)
{
	FontIterator it = m_fonts.find(name);
	if(it == m_fonts.end())
	{
		sf::Font* data = new sf::Font();
		data->loadFromFile(path);
		m_fonts[name] = data;
		return data;
	}
	return it->second;
}

/*virtual*/ bool ResourceManager::loadFontsFromData(Data& data, bool destroyExisting)
{
	std::vector<file_info> infos = data.getFonts();
	for(std::vector<file_info>::iterator it = infos.begin(); it != infos.end(); ++it)
	{
		std::vector<std::string> words = splitString(splitString(it->file_name, '.')[0], '_');
		std::string resultName = "";
		for(uint32_t i = 0; i < words.size(); ++i)
		{
			if(i != 0)
			{
				resultName += ' ';
			}
			if(words[i][0] >= 'a' && words[i][0] <= 'z')
			{
				words[i][0] = words[i][0] + 'A' - 'a';
			}
			resultName += words[i];
		}
		sf::Font* data = new sf::Font();
		data->loadFromMemory(it->data, it->file_size);
		m_fonts[resultName] = data;
	}
	return true;
}

/*virtual*/ sf::Font* ResourceManager::getFont(const std::string& name) const
{
	FontIterator it = m_fonts.find(name);
	if(it == m_fonts.end())
	{
		return nullptr;
	}
	return it->second;
}

/*virtual*/ void ResourceManager::releaseFont(const std::string& name)
{
	FontIterator it = m_fonts.find(name);
	if(it != m_fonts.end())
	{
		delete it->second;
		m_fonts.erase(it);
	}
}

/*virtual*/ sf::Music* ResourceManager::registerMusic(const std::string& path, const std::string& name)
{
	MusicIterator it = m_musics.find(name);
	if(it == m_musics.end())
	{
		sf::Music* data = new sf::Music();
		data->openFromFile(path);
		MusicResource mr;
		mr.music = data;
		mr.loadedFromMemory = false;
		mr.data = nullptr;
		m_musics[name] = mr;
		return data;
	}
	return (it->second).music;
}

/*virtual*/ bool ResourceManager::loadMusicsFromData(Data& data, bool destroyExisting)
{
	std::vector<file_info> infos = data.getMusics();
	for(std::vector<file_info>::iterator it = infos.begin(); it != infos.end(); ++it)
	{
		std::vector<std::string> words = splitString(splitString(it->file_name, '.')[0], '_');
		std::string resultName = "";
		for(uint32_t i = 0; i < words.size(); ++i)
		{
			if(i != 0)
			{
				resultName += ' ';
			}
			if(words[i][0] >= 'a' && words[i][0] <= 'z')
			{
				words[i][0] = words[i][0] + 'A' - 'a';
			}
			resultName += words[i];
		}
		sf::Music* data = new sf::Music();
		data->openFromMemory(it->data, it->file_size);
		MusicResource mr;
		mr.music = data;
		mr.loadedFromMemory = true;
		mr.data = it->data;
		m_musics[resultName] = mr;
	}
	return true;
}

/*virtual*/ sf::Music* ResourceManager::getMusic(const std::string& name) const
{
	MusicIterator it = m_musics.find(name);
	if(it == m_musics.end())
	{
		return nullptr;
	}
	return (it->second).music;
}

/*virtual*/ void ResourceManager::releaseMusic(const std::string& name)
{
	MusicIterator it = m_musics.find(name);
	if(it != m_musics.end())
	{
		if((it->second).loadedFromMemory)
		{
			delete [] (it->second).data;
		}
		delete (it->second).music;
		m_musics.erase(it);
	}
}

/*virtual*/ sf::SoundBuffer* ResourceManager::registerSound(const std::string& path, const std::string& name)
{
	SoundIterator it = m_sounds.find(name);
	if(it == m_sounds.end())
	{
		sf::SoundBuffer* data = new sf::SoundBuffer();
		data->loadFromFile(path);
		m_sounds[name] = data;
		return data;
	}
	return it->second;
}

/*virtual*/ bool ResourceManager::loadSoundsFromData(Data& data, bool destroyExisting)
{
	std::vector<file_info> infos = data.getSounds();
	for(std::vector<file_info>::iterator it = infos.begin(); it != infos.end(); ++it)
	{
		std::vector<std::string> words = splitString(splitString(it->file_name, '.')[0], '_');
		std::string resultName = "";
		for(uint32_t i = 0; i < words.size(); ++i)
		{
			if(i != 0)
			{
				resultName += ' ';
			}
			if(words[i][0] >= 'a' && words[i][0] <= 'z')
			{
				words[i][0] = words[i][0] + 'A' - 'a';
			}
			resultName += words[i];
		}
		sf::SoundBuffer* data = new sf::SoundBuffer();
		data->loadFromMemory(it->data, it->file_size);
		m_sounds[resultName] = data;
	}
	return true;
}

/*virtual*/ sf::SoundBuffer* ResourceManager::getSound(const std::string& name) const
{
	SoundIterator it = m_sounds.find(name);
	if(it == m_sounds.end())
	{
		return nullptr;
	}
	return it->second;
}

/*virtual*/ void ResourceManager::releaseSound(const std::string& name)
{
	SoundIterator it = m_sounds.find(name);
	if(it != m_sounds.end())
	{
		delete it->second;
		m_sounds.erase(it);
	}
}

/*static*/ ResourceManager* ResourceManager::Initialize()
{
	if(s_instance == nullptr)
	{
		s_instance = new ResourceManager();
	}
	return s_instance;
}

/*static*/ ResourceManager* ResourceManager::Instance()
{
	return s_instance;
}

/*static*/ void ResourceManager::Destroy()
{
	if(s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

/*static*/ ResourceManager* ResourceManager::s_instance = nullptr;
