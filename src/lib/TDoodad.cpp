#include "../include/TDoodad.hpp"
#include "../include/tinyxml2.h"
#include <dirent.h>

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
                file = tower_path + "/" + file;

				if(!load_towerFile(file))
                {
                    return false;
                }
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

bool TDoodad::load_towerFile(std::string& tower_file_path)
{
    printf("%s\n",tower_file_path.c_str());
	tinyxml2::XMLDocument level_file;

    tinyxml2::XMLError error =  level_file.LoadFile(tower_file_path.c_str());

	if(tinyxml2::XML_NO_ERROR != error)
    {
        fprintf(stderr, "erreur %d lors de l'ouverture du fichier \" %s \".\n", error, tower_file_path.c_str());
		return false;
    }

    tinyxml2::XMLElement* tower = level_file.RootElement();

    Range rangeTower;
    rangeTower.minimal = tower->FirstChildElement("attack")->FirstChildElement("range")->FloatAttribute("minimal");
    rangeTower.maximal = tower->FirstChildElement("attack")->FirstChildElement("range")->FloatAttribute("maximal");

    Attack attackTower;
    attackTower.damage = tower->FirstChildElement("attack")->FloatAttribute("damage");
    attackTower.speed = tower->FirstChildElement("attack")->FloatAttribute("speed");
    attackTower.range = rangeTower;
    attackTower.availableTarget[UnitType::GROUND] = tower->FirstChildElement("attack")->FirstChildElement("target")->BoolAttribute("ground");
    attackTower.availableTarget[UnitType::AIR] = tower->FirstChildElement("attack")->FirstChildElement("target")->BoolAttribute("air");
    attackTower.availableTarget[UnitType::WATER] = tower->FirstChildElement("attack")->FirstChildElement("target")->BoolAttribute("water");

	Foundation foundationTower;
	foundationTower.size = tower->FirstChildElement("construction")->FirstChildElement("foundation")->IntAttribute("size");

	switch (tower->FirstChildElement("construction")->FirstChildElement("foundation")->Attribute("type")[0])
	{
    case 'g':   // ground
        foundationTower.type = UnitType::GROUND;
        break;
    case 'a':   // air
        foundationTower.type = UnitType::AIR;
        break;
    case 'w':   // water
        foundationTower.type = UnitType::WATER;
        break;
    default:
        foundationTower.type = UnitType::GROUND;
        break;
	}

    Construction constructionTower;
	constructionTower.cost = tower->FirstChildElement("construction")->IntAttribute("cost");
	constructionTower.time = tower->FirstChildElement("construction")->FloatAttribute("time");
	constructionTower.foundation = foundationTower;

    m_ttower.push_back(new TTower(tower->IntAttribute("id"), std::string(tower->FirstChildElement("name")->GetText()), attackTower, constructionTower));

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
	std::string file;

	while ((content = readdir(rep)) != NULL)
	{
		file = std::string(content->d_name);

		if(-1 != (int)file.find(".xml"))
		{
			if(".xml" == (file.substr(file.length()-4, file.length()-1)))
			{
                file = creep_path + "/" + file;

				if(!load_creepFile(file))
                {
                    return false;
                }
			}
		}
	}

	if (-1 == closedir(rep))
	{
		fprintf(stderr, "erreur lors de la fermeture du dossier \" %s \".\n", creep_path.c_str());
		return false;
	}

	return true;
}

bool TDoodad::load_creepFile(std::string& creep_file_path)
{
    printf("%s\n",creep_file_path.c_str());
	tinyxml2::XMLDocument level_file;

    tinyxml2::XMLError error =  level_file.LoadFile(creep_file_path.c_str());

	if(tinyxml2::XML_NO_ERROR != error)
    {
        fprintf(stderr, "erreur %d lors de l'ouverture du fichier \" %s \".\n", error, creep_file_path.c_str());
		return false;
    }

    tinyxml2::XMLElement* creep = level_file.RootElement();

    Movement movementCreep;
    movementCreep.speed = creep->FirstChildElement("movement")->FloatAttribute("speed");
    switch (creep->FirstChildElement("movement")->Attribute("type")[0])
	{
    case 'g':   // ground
        movementCreep.type = UnitType::GROUND;
        break;
    case 'a':   // air
        movementCreep.type = UnitType::AIR;
        break;
    case 'w':   // water
        movementCreep.type = UnitType::WATER;
        break;
    default:
        movementCreep.type = UnitType::GROUND;
        break;
	}

    Stats statsCreep;
    statsCreep.bounty = creep->FirstChildElement("stats")->IntAttribute("bounty");
    statsCreep.health = creep->FirstChildElement("stats")->FloatAttribute("health");
    statsCreep.health_regen = creep->FirstChildElement("stats")->FloatAttribute("health_regen");

    m_tcreep.push_back(new TCreep(creep->IntAttribute("id"), std::string(creep->FirstChildElement("name")->GetText()), movementCreep, statsCreep));

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

TTower* TDoodad::getTower(int i)
{
    return TDoodad::m_ttower[i];
}

std::vector<TTower*> TDoodad::m_ttower;
std::vector<TCreep*> TDoodad::m_tcreep;
