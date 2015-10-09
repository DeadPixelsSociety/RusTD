#include "../include/ResourceManager.hpp"

typedef std::map<std::string, sf::Texture*>::const_iterator TextureIterator;
typedef std::map<std::string, sf::Font*>::const_iterator FontIterator;
typedef std::map<std::string, sf::Music*>::const_iterator MusicIterator;
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
		delete it->second;
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
		m_musics[name] = data;
		return data;
	}
	return it->second;
}

/*virtual*/ sf::Music* ResourceManager::getMusic(const std::string& name) const
{
	MusicIterator it = m_musics.find(name);
	if(it == m_musics.end())
	{
		return nullptr;
	}
	return it->second;
}

/*virtual*/ void ResourceManager::releaseMusic(const std::string& name)
{
	MusicIterator it = m_musics.find(name);
	if(it != m_musics.end())
	{
		delete it->second;
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
