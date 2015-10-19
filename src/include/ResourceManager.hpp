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
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "DataCompiler.hpp"

struct MusicResource
{
	sf::Music* music;
	bool loadedFromMemory;
	char* data;
};

class ResourceManager
{
public:

	explicit ResourceManager(void);

	virtual ~ResourceManager(void);

	virtual sf::Texture* registerTexture(const std::string& path, const std::string& name);
	virtual bool loadTexturesFromData(Data& data, bool destroyExisting = true);
	virtual sf::Texture* getTexture(const std::string& name) const;
	virtual void releaseTexture(const std::string& name);

	virtual sf::Font* registerFont(const std::string& path, const std::string& name);
	virtual bool loadFontsFromData(Data& data, bool destroyExisting = true);
	virtual sf::Font* getFont(const std::string& name) const;
	virtual void releaseFont(const std::string& name);

	virtual sf::Music* registerMusic(const std::string& path, const std::string& name);
	virtual bool loadMusicsFromData(Data& data, bool destroyExisting = true);
	virtual sf::Music* getMusic(const std::string& name) const;
	virtual void releaseMusic(const std::string& name);

	virtual sf::SoundBuffer* registerSound(const std::string& path, const std::string& name);
	virtual bool loadSoundsFromData(Data& data, bool destroyExisting = true);
	virtual sf::SoundBuffer* getSound(const std::string& name) const;
	virtual void releaseSound(const std::string& name);


	static ResourceManager* Initialize(void);
	static ResourceManager* Instance(void);
	static void Destroy(void);

protected:

	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, sf::Font*> m_fonts;
	std::map<std::string, MusicResource> m_musics;
	std::map<std::string, sf::SoundBuffer*> m_sounds;

	static ResourceManager* s_instance;

private:

}; // class ResourceManager

#endif // RESOURCEMANAGER_HPP
