#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class ResourceManager
{
public:

	explicit ResourceManager(void);

	virtual ~ResourceManager(void);

	virtual sf::Texture* registerTexture(const std::string& path, const std::string& name);
	virtual sf::Texture* getTexture(const std::string& name) const;
	virtual void releaseTexture(const std::string& name);

	virtual sf::Font* registerFont(const std::string& path, const std::string& name);
	virtual sf::Font* getFont(const std::string& name) const;
	virtual void releaseFont(const std::string& name);

	virtual sf::Music* registerMusic(const std::string& path, const std::string& name);
	virtual sf::Music* getMusic(const std::string& name) const;
	virtual void releaseMusic(const std::string& name);

	virtual sf::SoundBuffer* registerSound(const std::string& path, const std::string& name);
	virtual sf::SoundBuffer* getSound(const std::string& name) const;
	virtual void releaseSound(const std::string& name);


	static ResourceManager* Initialize(void);
	static ResourceManager* Instance(void);
	static void Destroy(void);

protected:

	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, sf::Font*> m_fonts;
	std::map<std::string, sf::Music*> m_musics;
	std::map<std::string, sf::SoundBuffer*> m_sounds;

	static ResourceManager* s_instance;

private:

}; // class ResourceManager

#endif // RESOURCEMANAGER_HPP
