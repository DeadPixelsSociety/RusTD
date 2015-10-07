#include "../include/TDoodad.hpp"
#include <dirent.h>
#include "../include/tinyxml2.h"

TDoodad::TDoodad(void)
{}

TDoodad::~TDoodad(void)
{}

bool TDoodad::load_XML(std::string& share_path)
{
	std::string tower_path(share_path + "/tower");
	std::string creep_path(share_path + "/creep");

	return load_towerXML(tower_path) && load_creepXML(creep_path);
}

bool TDoodad::load_towerXML(std::string& tower_path)
{
    /*
	tinyxml2::XMLDocument level_file;
	level_file.LoadFile(path_file);

	tinyxml2::XMLElement* elem = level_file.RootElement();

	tinyxml2::XMLElement* tower = elem->FirstChildElement("tower");
	tinyxml2::XMLElement* id = tower->FirstChildElement("id");

	printf("%s\n",id->getText());
	*/

	DIR* rep = opendir(tower_path.c_str());

	if (NULL == rep)
	{	
		fprintf(stderr, "Impossible d'ouvrir le dossier \" %s \".\n", tower_path.c_str());
		return false;
	}

	struct dirent* content = readdir(rep);
	std::string file;

	while ((content = readdir(rep)) != NULL)
	{
		file = std::string(content->d_name);
		if(-1 != (int)file.find(".xml"))
		{
			if(".xml" == (file.substr(file.length()-4, file.length()-1)))
			{
				load_towerFile(file);
			}
		}
	}

	if (-1 == closedir(rep))
	{
		fprintf(stderr, "erreur lors de la fermeture du dossier \" %s \".\n", tower_path.c_str());
		return false;
	}

	return true;
}

bool TDoodad::load_creepXML(std::string& creep_path)
{
	DIR* rep = opendir(creep_path.c_str());

	if (NULL == rep)
	{	
		fprintf(stderr, "Impossible d'ouvrir le dossier \" %s \".\n", creep_path.c_str());
		return false;
	}

	struct dirent* content = readdir(rep);

	while ((content = readdir(rep)) != NULL)
	{
		//if(
		printf("%s\n", content->d_name);
	}

	if (-1 == closedir(rep))
	{
		fprintf(stderr, "erreur lors de la fermeture du dossier \" %s \".\n", creep_path.c_str());
		return false;
	}

	return true;
}

bool TDoodad::load_towerFile(std::string& tower_file_path)
{
	tinyxml2::XMLDocument level_file;
	level_file.LoadFile(tower_file_path.c_str());

	tinyxml2::XMLElement* tower = level_file.RootElement();

	printf("%s\n", tower_file_path.c_str());

	int y=tower->IntAttribute("id");
	//printf("%d\n", tower->IntAttribute("id"));

	return true;
}

bool TDoodad::load_creepFile(std::string& creep_file_path)
{
	tinyxml2::XMLDocument level_file;
	level_file.LoadFile(creep_file_path.c_str());

	tinyxml2::XMLElement* tower = level_file.RootElement()->FirstChildElement("tower");

	printf("%d\n", tower->IntAttribute("id"));

	return true;
}

void TDoodad::destroy_objects()
{
	TTower* tmpt;
	TCreep* tmpc;

	while(!m_ttower.empty())
	{
		tmpt = m_ttower.back();
		delete tmpt;
		m_ttower.pop_back();
	}

	while(!m_tcreep.empty())
	{
		tmpc = m_tcreep.back();
		delete tmpc;
		m_tcreep.pop_back();
	}
}

std::vector<TTower*> TDoodad::m_ttower;
std::vector<TCreep*> TDoodad::m_tcreep;
