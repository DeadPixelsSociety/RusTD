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
#include "../include/TDoodad.hpp"
#include "../include/tinyxml2.h"
#include <dirent.h>
#include <iostream>

TDoodad::TDoodad()
{}

TDoodad::~TDoodad()
{}

bool TDoodad::load_XML(const std::string& share_path)
{
	std::string tower_path(share_path + "/tower");
	std::string creep_path(share_path + "/creep");

	return load_towerXML(tower_path) && load_creepXML(creep_path);
}

bool TDoodad::load_towerXML(const std::string& tower_path)
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

bool TDoodad::load_towerFile(const std::string& tower_file_path)
{
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
    attackTower.period = tower->FirstChildElement("attack")->FloatAttribute("period");
    attackTower.damage_base = tower->FirstChildElement("attack")->FloatAttribute("damage_base");
	attackTower.damage_bonus = tower->FirstChildElement("attack")->FloatAttribute("damage_bonus");
    attackTower.projectile_velocity = tower->FirstChildElement("attack")->FloatAttribute("projectile_velocity");

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

	int id = tower->IntAttribute("id");
	if(m_ttower.find(id) != m_ttower.end())
	{
		fprintf(stderr, "TTower with id [%d] already exists.\n", id);
		return false;
	}

	m_ttower[id] = new TTower(id, std::string(tower->FirstChildElement("name")->GetText()), attackTower, constructionTower);

	tinyxml2::XMLElement* resource = tower->FirstChildElement("resource");
	m_ttower[id]->setIdent(
		resource->FirstChildElement("icon")->GetText(),
		resource->FirstChildElement("base")->GetText(),
		resource->FirstChildElement("head")->GetText(),
		resource->FirstChildElement("projectile")->GetText(),
		resource->FirstChildElement("splash")->GetText()
		);

	return true;
}

bool TDoodad::load_creepXML(const std::string& creep_path)
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

bool TDoodad::load_creepFile(const std::string& creep_file_path)
{
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
    statsCreep.health_base = creep->FirstChildElement("stats")->FloatAttribute("health_base");
	statsCreep.health_bonus = creep->FirstChildElement("stats")->FloatAttribute("health_bonus");
	statsCreep.health_regen = creep->FirstChildElement("stats")->FloatAttribute("health_regen");
    statsCreep.bounty_base = creep->FirstChildElement("stats")->IntAttribute("bounty_base");
	statsCreep.bounty_coefficient = creep->FirstChildElement("stats")->IntAttribute("bounty_coefficient");

	int id = creep->IntAttribute("id");
	if(m_tcreep.find(id) == m_tcreep.end())
	{
		m_tcreep[id] = new TCreep(id, std::string(creep->FirstChildElement("name")->GetText()), movementCreep, statsCreep);
	}
	else
	{
		fprintf(stderr, "TCreep with id [%d] already exists.\n", id);
	}

	return true;
}

void TDoodad::destroy_objects()
{
	for(std::map<int,TTower*>::iterator it = m_ttower.begin(); it != m_ttower.end(); ++it)
	{
		delete it->second;
	}
	for(std::map<int,TCreep*>::iterator it = m_tcreep.begin(); it != m_tcreep.end(); ++it)
	{
		delete it->second;
	}
	for(std::map<int,Animation*>::iterator it = m_animation.begin(); it != m_animation.end(); ++it)
	{
		delete it->second;
	}
}
#ifndef DATA_COMPILER
bool TDoodad::load_Data(Data& data, bool destroyExisting)
{
	std::vector<TCreep*> tc = data.getTCreeps();
	std::vector<TTower*> tt = data.getTTowers();
	std::vector<Animation*> anim = data.getAnimations();
	if(destroyExisting)
	{
		destroy_objects();
	}
	for(uint32_t i = 0; i < tc.size(); ++i)
	{
		m_tcreep[tc[i]->getId()] = tc[i];
	}
	for(uint32_t i = 0; i < tt.size(); ++i)
	{
		m_ttower[tt[i]->getId()] = tt[i];
	}
	for(uint32_t i = 0; i < anim.size(); ++i)
	{
		m_animation[anim[i]->getId()] = anim[i];
	}
	return true;
}
#endif

TCreep* TDoodad::getTCreep(int i)
{
	std::map<int,TCreep*>::iterator it = m_tcreep.find(i);
	if(it == m_tcreep.end())
	{
		std::cerr << "Not found : TCreep with id [" << i << "]" << std::endl;
		return nullptr;
	}
	return it->second;
}

TTower* TDoodad::getTTower(int i)
{
    std::map<int,TTower*>::iterator it = m_ttower.find(i);
	if(it == m_ttower.end())
	{
		std::cerr << "Not found : TTower with id [" << i << "]" << std::endl;
		return nullptr;
	}
	return it->second;
}

Animation* TDoodad::getAnimation(int i)
{
    std::map<int,Animation*>::iterator it = m_animation.find(i);
	if(it == m_animation.end())
	{
		std::cerr << "Not found : Animation with id [" << i << "]" << std::endl;
		return nullptr;
	}
	return it->second;
}

std::vector<int> TDoodad::getTCreepIds()
{
	std::vector<int> out;
	for(std::map<int, TCreep*>::iterator it = m_tcreep.begin(); it != m_tcreep.end(); ++it)
	{
		out.push_back(it->first);
	}
	return out;
}

std::vector<int> TDoodad::getTTowerIds()
{
	std::vector<int> out;
	for(std::map<int, TTower*>::iterator it = m_ttower.begin(); it != m_ttower.end(); ++it)
	{
		out.push_back(it->first);
	}
	return out;
}

std::vector<int> TDoodad::getAnimationIds()
{
	std::vector<int> out;
	for(std::map<int, Animation*>::iterator it = m_animation.begin(); it != m_animation.end(); ++it)
	{
		out.push_back(it->first);
	}
	return out;
}

std::map<int, TTower*> TDoodad::m_ttower;
std::map<int, TCreep*> TDoodad::m_tcreep;
std::map<int, Animation*> TDoodad::m_animation;
