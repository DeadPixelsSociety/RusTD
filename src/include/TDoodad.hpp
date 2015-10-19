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
#ifndef TDOODAD_H
#define TDOODAD_H

#include "TTower.hpp"
#include "TCreep.hpp"
#include "Animation.hpp"
#include "DataCompiler.hpp"
#include "config.hpp"

class TDoodad
{
public:
	~TDoodad(void);

	static bool load_XML(const std::string& share_path = std::string("../src/share"));
	static bool load_towerXML(const std::string& tower_path);
	static bool load_towerFile(const std::string& tower_file_path);
	static bool load_creepXML(const std::string& creep_path);
	static bool load_creepFile(const std::string& creep_file_path);
	static void destroy_objects();

#ifndef DATA_COMPILER
	static bool load_Data(Data& data, bool destroyExisting = true);
#endif

    static TCreep* getTCreep(int i);
    static TTower* getTTower(int i);
    static Animation* getAnimation(int i);

    static std::vector<int> getTCreepIds(void);
    static std::vector<int> getTTowerIds(void);
    static std::vector<int> getAnimationIds(void);

    //static TCreep* getTCreepByID(int id);
    //static TTower* getTTowerByID(int id);

protected:
	static std::map<int, TTower*> m_ttower;
	static std::map<int, TCreep*> m_tcreep;
	static std::map<int, Animation*> m_animation;

private:
	TDoodad(void);
};

#endif
