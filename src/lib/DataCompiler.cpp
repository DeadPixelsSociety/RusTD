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
#include "../include/DataCompiler.hpp"
#include "../include/TDoodad.hpp"
#include <fstream>

std::vector<char>* mask = nullptr;
int mask_pointer = 0;
char control_sum = 0;

uint8_t getByte(uint32_t uinteger, int b0_to_3)
{
	type32_converter tc;
	tc.uinteger = uinteger;
	return getByte(tc, b0_to_3);
}

uint32_t setByte(uint32_t uinteger, int b0_to_3, uint8_t b)
{
	type32_converter tc;
	tc.uinteger = uinteger;
	return setByte(tc, b0_to_3, b).uinteger;
}

uint8_t getByte(int32_t integer, int b0_to_3)
{
	type32_converter tc;
	tc.integer = integer;
	return getByte(tc, b0_to_3);
}

int32_t setByte(int32_t integer, int b0_to_3, uint8_t b)
{
	type32_converter tc;
	tc.integer = integer;
	return setByte(tc, b0_to_3, b).integer;
}

uint8_t getByte(float real, int b0_to_3)
{
	type32_converter tc;
	tc.real = real;
	return getByte(tc, b0_to_3);
}

float setByte(float real, int b0_to_3, uint8_t b)
{
	type32_converter tc;
	tc.real = real;
	return setByte(tc, b0_to_3, b).real;
}

uint8_t getByte(type32_converter tc, int b0_to_3)
{
	byte_accessor ba;
	ba.value = tc;
	switch(b0_to_3)
	{
	case 0:
		return ba.bytes.byte0;
	case 1:
		return ba.bytes.byte1;
	case 2:
		return ba.bytes.byte2;
	case 3:
		return ba.bytes.byte3;
	default:
		return 0;
	}
}

type32_converter setByte(type32_converter tc, int b0_to_3, uint8_t b)
{
	byte_accessor ba;
	ba.value = tc;
	switch(b0_to_3)
	{
	case 0:
		ba.bytes.byte0 = b;
		return ba.value;
	case 1:
		ba.bytes.byte1 = b;
		return ba.value;
	case 2:
		ba.bytes.byte2 = b;
		return ba.value;
	case 3:
		ba.bytes.byte3 = b;
		return ba.value;
	default:
		return type32_converter();
	}
}

#include <iostream>

int dc_error()
{
	std::cerr << "Aborted !" << std::endl;
	system("PAUSE");
	return 1;
}

int bitcount(int in)
{
	int i;
	int out = 0;
	for(i = 0; i < 8; ++i)
	{
		if(in % 2 == 1)out++;
		in = in >> 1;
	}
	return out;
}

#ifdef DATA_COMPILER

bool dc_compileCreep(TCreep* tc, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(nullptr == tc)return false;
	int id = tc->getId();
	std::string name = tc->getName();
	Movement movement = tc->getMovement();
	int movement_type = (int)(movement.type);
	Stats stats = tc->getStats();
	if(!dc_compileInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(movement_type), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(movement.speed), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(stats.health), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(stats.health_regen), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(stats.bounty), data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileTower(TTower* tt, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(nullptr == tt)return false;
	int id = tt->getId();
	char trueChar = 't', falseChar = 'f';
	std::string name = tt->getName();
	std::vector<int> upgrades = tt->getUpgrades();
	int usize = upgrades.size();
	Attack attack = tt->getAttack();
	Construction construction = tt->getConstruction();
	int construction_foundation_type = (int)(construction.foundation.type);
	if(!dc_compileInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&usize, data_bloc, data_pointer, bloc_size))return false;
	for(uint32_t i = 0; i < upgrades.size(); ++i)
	{
		int uid = upgrades[i];
		if(!dc_compileInteger(&(uid), data_bloc, data_pointer, bloc_size))return false;
	}
	if(!dc_compileFloat(&(attack.damage), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(attack.speed), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(attack.range.minimal), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(attack.range.maximal), data_bloc, data_pointer, bloc_size))return false;
	for(int i = 0; i < (int)(UnitType::UNITTYPE_COUNT); ++i)
	{
		if(attack.availableTarget[i])
		{
			if(!dc_compileChar(&trueChar, data_bloc, data_pointer, bloc_size))return false;
		}
		else
		{
			if(!dc_compileChar(&falseChar, data_bloc, data_pointer, bloc_size))return false;
		}
	}
	if(!dc_compileInteger(&(construction.cost), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&(construction.time), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(construction.foundation.size), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(construction_foundation_type), data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileAnimation(Animation* anim, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(nullptr == anim)return false;
	int id = anim->getId();
	std::string name = anim->getName();
	sf::IntRect rect = anim->getOriginalRect();
	float ft = anim->getFrameTime();
	int fc = anim->getFrameCount();
	if(!dc_compileInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(rect.top), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(rect.left), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(rect.width), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&(rect.height), data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileFloat(&ft, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileInteger(&fc, data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileString(std::string* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4 + (int)(value->size()))return false;
	type32_converter tc;
	tc.uinteger = value->size();
	if(!dc_compileInteger(&(tc.integer), data_bloc, data_pointer, bloc_size))return false;
	for(uint32_t i = 0; i < tc.uinteger; ++i)
	{
		if(!dc_compileChar(&((*value)[i]), data_bloc, data_pointer, bloc_size))return false;
	}
	return true;
}

bool dc_compileInteger(int* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4)return false;
	type8_converter t8c;
	t8c.ubyte = getByte(*value, 0);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 1);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 2);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 3);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileFloat(float* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4)return false;
	type8_converter t8c;
	t8c.ubyte = getByte(*value, 0);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 1);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 2);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(*value, 3);
	if(!dc_compileChar(&(t8c.schar), data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileChar(char* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
	type8_converter t8c;
	t8c.byte = *value;
#ifdef HIDE_DATA
	data_bloc[*data_pointer] = t8c.ubyte ^ (*mask)[mask_pointer];
#else
	data_bloc[*data_pointer] = t8c.ubyte;
#endif
	control_sum = control_sum ^ data_bloc[*data_pointer];
	++mask_pointer;
	if(mask_pointer >= (int)(mask->size()))mask_pointer = 0;
	++(*data_pointer);
	return true;
}

bool dc_exportData(const std::string& filename, data_byte data_bloc, int bloc_size)
{
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
	if(!out.good() || !out.is_open())return false;
	out.write(data_bloc, bloc_size);
	out.close();
	return true;
}

#include <dirent.h>

int main(int argc, char** argv)
{
	// Build mask
	if(nullptr != mask)delete mask;
	mask = new std::vector<char>();
	for(int i = 0; i < 0x100; ++i)
	{
		if(bitcount(i) == 4)
		{
			mask->push_back((char)(i & 0xff));
		}
	}
	// Rotate mask start
	int key_sum = 0;
	std::string key(CRYPT_KEY);
	for(uint32_t i = 0; i < key.size(); ++i)
	{
		key_sum += (int)(key[i]);
	}
	mask_pointer = (key_sum) % mask->size();
	control_sum = (char)0;
	int alloc_size = 1; // Reserve one byte for control sum;
	int tmp;
	struct data_save ds;

	// COUNT UNITS ////////////////////////////////////////////////////////////
	if(COMPILE_UNITS)
	{
		std::cout << "Counting units" << std::endl;
		if(!TDoodad::load_XML(SHARE_DIR))
		{
			std::cerr << "Error when loading xml files" << std::endl;
			return dc_error();
		}
		TCreep* tc = nullptr;
		TTower* tt = nullptr;
		Animation* anim = nullptr;
		std::cout << "Counting TCreep elements..." << std::endl;
		std::vector<int> ids = TDoodad::getTCreepIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			tc = TDoodad::getTCreep(ids[i]);
			++ds.tc_count;
			alloc_size += 28 + tc->getName().size();
			std::cout << ds.tc_count << " - Allocation size: " << alloc_size << "\n";
		}
		std::cout << "Counting TTower elements..." << std::endl;
		ids = TDoodad::getTTowerIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			tt = TDoodad::getTTower(ids[i]);
			++ds.tt_count;
			alloc_size += 40 + tt->getUpgrades().size() + (int)(UnitType::UNITTYPE_COUNT) + tt->getName().size();
			std::cout << ds.tt_count << " - Allocation size: " << alloc_size << "\n";
		}
		std::cout << "Counting Animation elements..." << std::endl;
		ids = TDoodad::getAnimationIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			anim = TDoodad::getAnimation(ids[i]);
			++ds.anim_count;
			alloc_size += 32 + anim->getName().size();
			std::cout << ds.anim_count << " - Allocation size: " << alloc_size << "\n";
		}
		alloc_size += 12;
	}

	// COUNT TEXTURES /////////////////////////////////////////////////////////
	if(COMPILE_TEXTURES)
	{
		std::cout << "Counting textures" << std::endl;
		DIR* rep = opendir(SHARE_DIR"/texture");
		if (NULL == rep)
		{
			std::cerr << "Error when opening directory \"" << SHARE_DIR << "/texture\"" << std::endl;
			return dc_error();
		}
		struct dirent* content = readdir(rep);
		int count_textures = 0;
		while(NULL != (content = readdir(rep)))
		{
			++count_textures;
			file_info fi;
			fi.file_name = std::string(content->d_name);

			if(-1 != (int)fi.file_name.find(".png"))
			{
				if(".png" == (fi.file_name.substr(fi.file_name.length()-4, fi.file_name.length()-1)))
				{
					alloc_size += 4 + fi.file_name.size();
					fi.file_path = SHARE_DIR"/texture/" + fi.file_name;
					std::ifstream f(fi.file_path.c_str(), std::ios::ate | std::ios::binary);
					if(!f.good())
					{
						std::cerr << "Error when opening file \"" << fi.file_path << "\"" << std::endl;
						return dc_error();
					}
					fi.file_size = f.tellg();
					alloc_size += 4 + fi.file_size;
					ds.texture_files.push_back(fi);
					f.close();
				}
			}
			std::cout << count_textures << " - Allocation size: " << alloc_size << "\n";
		}
		if (-1 == closedir(rep))
		{
			std::cerr << "Error when closing directory \"" << SHARE_DIR << "/texture\"" << std::endl;
			return dc_error();
		}
	}

	// COUNT FONTS ////////////////////////////////////////////////////////////
	if(COMPILE_FONTS)
	{
		std::cout << "Counting fonts" << std::endl;
		DIR* rep = opendir(SHARE_DIR"/font");
		if (NULL == rep)
		{
			std::cerr << "Error when opening directory \"" << SHARE_DIR << "/font\"" << std::endl;
			return dc_error();
		}
		struct dirent* content = readdir(rep);
		int count_fonts = 0;
		while(NULL != (content = readdir(rep)))
		{
			++count_fonts;
			file_info fi;
			fi.file_name = std::string(content->d_name);

			if(-1 != (int)fi.file_name.find(".ttf"))
			{
				if(".ttf" == (fi.file_name.substr(fi.file_name.length()-4, fi.file_name.length()-1)))
				{
					alloc_size += 4 + fi.file_name.size();
					fi.file_path = SHARE_DIR"/font/" + fi.file_name;
					std::ifstream f(fi.file_path.c_str(), std::ios::ate | std::ios::binary);
					if(!f.good())
					{
						std::cerr << "Error when opening file \"" << fi.file_path << "\"" << std::endl;
						return dc_error();
					}
					fi.file_size = f.tellg();
					alloc_size += 4 + fi.file_size;
					ds.font_files.push_back(fi);
					f.close();
				}
			}
			std::cout << count_fonts << " - Allocation size: " << alloc_size << "\n";
		}
		if (-1 == closedir(rep))
		{
			std::cerr << "Error when closing directory \"" << SHARE_DIR << "/font\"" << std::endl;
			return dc_error();
		}
	}

	// CREATE DATA ////////////////////////////////////////////////////////////
	std::cout << "Allocating data bloc" << std::endl;
	data_byte db = new char[alloc_size];
	int data_pointer = 0;

	// SAVE UNITS /////////////////////////////////////////////////////////////
	if(COMPILE_UNITS)
	{
		std::cout << "Compiling units" << std::endl;
		TCreep* tc = nullptr;
		TTower* tt = nullptr;
		Animation* anim = nullptr;
		dc_compileInteger(&(ds.tc_count), db, &data_pointer, alloc_size);
		tmp = ds.tc_count;
		ds.tc_count = 0;
		std::cout << "Compiling TCreep elements..." << std::endl;
		std::vector<int> ids = TDoodad::getTCreepIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			tc = TDoodad::getTCreep(ids[i]);
			++ds.tc_count;
			dc_compileCreep(tc, db, &data_pointer, alloc_size);
			std::cout << ds.tc_count << " / " << tmp << "\n";
		}
		dc_compileInteger(&(ds.tt_count), db, &data_pointer, alloc_size);
		tmp = ds.tt_count;
		ds.tt_count = 0;
		std::cout << "Compiling TTower elements..." << std::endl;
		ids = TDoodad::getTTowerIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			tt = TDoodad::getTTower(ids[i]);
			++ds.tt_count;
			dc_compileTower(tt, db, &data_pointer, alloc_size);
			std::cout << ds.tt_count << " / " << tmp << "\n";
		}
		dc_compileInteger(&(ds.anim_count), db, &data_pointer, alloc_size);
		tmp = ds.anim_count;
		ds.anim_count = 0;
		std::cout << "Compiling Animation elements..." << std::endl;
		ids = TDoodad::getAnimationIds();
		for(uint32_t i = 0; i < ids.size(); ++i)
		{
			anim = TDoodad::getAnimation(ids[i]);
			++ds.anim_count;
			dc_compileAnimation(anim, db, &data_pointer, alloc_size);
			std::cout << ds.anim_count << " / " << tmp << "\n";
		}
	}

	// SAVE TEXTURES //////////////////////////////////////////////////////////
	if(COMPILE_TEXTURES)
	{
		std::cout << "Compiling textures" << std::endl;
		int s = ds.texture_files.size();
		dc_compileInteger(&s, db, &data_pointer, alloc_size);
		std::cout << "0 / " << s << "\n";
        for(int i = 0; i < s; ++i)
		{
			dc_compileString(&(ds.texture_files[i].file_name), db, &data_pointer, alloc_size);
			dc_compileString(&(ds.texture_files[i].file_path), db, &data_pointer, alloc_size);
			dc_compileInteger(&(ds.texture_files[i].file_size), db, &data_pointer, alloc_size);
			std::ifstream f(ds.texture_files[i].file_path.c_str(), std::ios::in | std::ios::binary);
			if(!f.good())
			{
				std::cerr << "Error when opening file \"" << ds.texture_files[i].file_path << "\"" << std::endl;
				return dc_error();
			}
			for(int j = 0; j < ds.texture_files[i].file_size; ++j)
			{
				char c;
				f.read(&c, 1);
				dc_compileChar(&c, db, &data_pointer, alloc_size);
			}
			f.close();
			std::cout << i+1 << " / " << s << "\n";
		}
	}

	// SAVE FONTS /////////////////////////////////////////////////////////////
	if(COMPILE_FONTS)
	{
		std::cout << "Compiling fonts" << std::endl;
		int s = ds.font_files.size();
		dc_compileInteger(&s, db, &data_pointer, alloc_size);
		std::cout << "0 / " << s << "\n";
        for(int i = 0; i < s; ++i)
		{
			dc_compileString(&(ds.font_files[i].file_name), db, &data_pointer, alloc_size);
			dc_compileString(&(ds.font_files[i].file_path), db, &data_pointer, alloc_size);
			dc_compileInteger(&(ds.font_files[i].file_size), db, &data_pointer, alloc_size);
			std::ifstream f(ds.font_files[i].file_path.c_str(), std::ios::in | std::ios::binary);
			if(!f.good())
			{
				std::cerr << "Error when opening file \"" << ds.font_files[i].file_path << "\"" << std::endl;
				return dc_error();
			}
			for(int j = 0; j < ds.font_files[i].file_size; ++j)
			{
				char c;
				f.read(&c, 1);
				dc_compileChar(&c, db, &data_pointer, alloc_size);
			}
			f.close();
			std::cout << i+1 << " / " << s << "\n";
		}
	}

	// SAVE FILE //////////////////////////////////////////////////////////////
	db[data_pointer] = control_sum; // Add ckecksum (one byte)
	std::cout << "\nSaving file..." << std::endl;
	dc_exportData("data.bin", db, alloc_size);
	delete [] db;
	std::cout << "done !" << std::endl;
	system("PAUSE");
	return 0;
}

#else

bool dc_extractCreep(TCreep** tc, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	int id;
	std::string name;
	Movement movement;
	int movement_type;
	float movement_speed;
	Stats stats;
	float stats_health, stats_health_regen;
	int stats_bounty;
	if(!dc_extractInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&movement_type, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&movement_speed, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&stats_health, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&stats_health_regen, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&stats_bounty, data_bloc, data_pointer, bloc_size))return false;
	movement.type = (UnitType)movement_type;
	movement.speed = movement_speed;
	stats.health = stats_health;
	stats.health_regen = stats_health_regen;
	stats.bounty = stats_bounty;
	*tc = new TCreep(id, name, movement, stats);
	return true;
}

bool dc_extractTower(TTower** tt, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	int id;
	std::string name;
	std::vector<int> upgrades;
	int usize;
	Attack attack;
	float attack_damage, attack_speed;
	float attack_range_minimal, attack_range_maximal;
	bool attack_availableTarget[(int)UnitType::UNITTYPE_COUNT];
	Construction construction;
	int construction_cost;
	float construction_time;
	int construction_foundation_size, construction_foundation_type;
	if(!dc_extractInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&usize, data_bloc, data_pointer, bloc_size))return false;
	for(int i = 0; i < usize; ++i)
	{
		int u;
		if(!dc_extractInteger(&u, data_bloc, data_pointer, bloc_size))return false;
		upgrades.push_back(u);

	}
	if(!dc_extractFloat(&attack_damage, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&attack_speed, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&attack_range_minimal, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&attack_range_maximal, data_bloc, data_pointer, bloc_size))return false;
	for(int i = 0; i < (int)UnitType::UNITTYPE_COUNT; ++i)
	{
		char c;
		if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
		attack_availableTarget[i] = c == 't';
	}
	if(!dc_extractInteger(&construction_cost, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&construction_time, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&construction_foundation_size, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&construction_foundation_type, data_bloc, data_pointer, bloc_size))return false;
	attack.damage = attack_damage;
	attack.speed = attack_speed;
	attack.range.minimal = attack_range_minimal;
	attack.range.maximal = attack_range_maximal;
	for(int i = 0; i < (int)UnitType::UNITTYPE_COUNT; ++i)
	{
		attack.availableTarget[i] = attack_availableTarget[i];
	}
	construction.cost = construction_cost;
	construction.time = construction_time;
	construction.foundation.size = construction_foundation_size;
	construction.foundation.type = (UnitType)construction_foundation_type;
	*tt = new TTower(id, name, attack, construction);
	return true;
}

bool dc_extractAnimation(Animation** anim, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	int id;
	std::string name;
	int top, left, width, height;
	float frame_time;
	int frame_count;
	if(!dc_extractInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractString(&name, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&top, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&left, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&width, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&height, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractFloat(&frame_time, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_extractInteger(&frame_count, data_bloc, data_pointer, bloc_size))return false;
	*anim = new Animation(id, name, nullptr, sf::IntRect(top, left, width, height), frame_count, frame_time);
	return true;
}

bool dc_extractString(std::string* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
	int str_size;
	(*value) = "";
	if(!dc_extractInteger(&str_size, data_bloc, data_pointer, bloc_size))return false;
	for(int i = 0; i < str_size; ++i)
	{
		char c;
		if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
		(*value) += c;
	}
	return true;
}

bool dc_extractInteger(int* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
	type8_converter t8c;
	char c;
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 0, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 1, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 2, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 3, t8c.ubyte);
	return true;
}

bool dc_extractFloat(float* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
	type8_converter t8c;
	char c;
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 0, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 1, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 2, t8c.ubyte);
	if(!dc_extractChar(&c, data_bloc, data_pointer, bloc_size))return false;
	t8c.schar = c;
	*value = setByte(*value, 3, t8c.ubyte);
	return true;
}

bool dc_extractChar(char* value, data_byte data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
#ifdef HIDE_DATA
	*value = data_bloc[*data_pointer] ^ (*mask)[mask_pointer];
#else
	*value = data_bloc[*data_pointer];
#endif
	control_sum = control_sum ^ *value;
	++mask_pointer;
	if(mask_pointer >= (int)(mask->size()))mask_pointer = 0;
	++(*data_pointer);
	return true;
}

#define DATA_ERROR_READ_FILE 1
#define DATA_ERROR_CONTROL_SUM 2

Data::Data(const std::string& filename)
: m_state(0)
, m_ftc(false), m_ftt(false), m_fan(false), m_fte(false), m_ffo(false), m_fmu(false), m_fso(false)
{
	// Build mask
	if(nullptr != mask)delete mask;
	mask = new std::vector<char>();
	for(int i = 0; i < 0x100; ++i)
	{
		if(bitcount(i) == 4)
		{
			mask->push_back((char)(i & 0xff));
		}
	}
	// Rotate mask start
	int key_sum = 0;
	std::string key(CRYPT_KEY);
	for(uint32_t i = 0; i < key.size(); ++i)
	{
		key_sum += (int)(key[i]);
	}
	mask_pointer = (key_sum) % mask->size();
	control_sum = (char)0;

	std::ifstream file(filename.c_str(), std::ios::ate | std::ios::binary);
	if(!file.good())
	{
		m_state = DATA_ERROR_READ_FILE;
		return;
	}
	int file_size = file.tellg();
	file.seekg(std::ios_base::beg);
	data_byte db = new char[file_size];
	int data_pointer = 0;
	for(int i = 0; i < file_size - 1; ++i)
	{
		file.read(&(db[i]), 1);
		control_sum = control_sum ^ db[i];
	}
	if(control_sum != db[file_size - 1])
	{
		m_state = DATA_ERROR_CONTROL_SUM;
	}

	// LOAD UNITS /////////////////////////////////////////////////////////////
	if(COMPILE_UNITS)
	{
		std::cout << "Loading units" << std::endl;
		TCreep* tc = nullptr;
		TTower* tt = nullptr;
		Animation* anim = nullptr;
		int tc_count, tt_count, anim_count;
		std::cout << "Loading TCreep elements..." << std::endl;
		dc_extractInteger(&tc_count, db, &data_pointer, file_size);
		std::cout << "0 / " << tc_count << "\n";
		for(int i = 0; i < tc_count; ++i)
		{
			dc_extractCreep(&tc, db, &data_pointer, file_size);
			m_tcreep.push_back(tc);
			std::cout << i+1 << " / " << tc_count << "\n";
		}
		std::cout << "Loading TTower elements..." << std::endl;
		dc_extractInteger(&tt_count, db, &data_pointer, file_size);
		std::cout << "0 / " << tt_count << "\n";
		for(int i = 0; i < tt_count; ++i)
		{
			dc_extractTower(&tt, db, &data_pointer, file_size);
			m_ttower.push_back(tt);
			std::cout << i+1 << " / " << tt_count << "\n";
		}
		std::cout << "Loading Animation elements..." << std::endl;
		dc_extractInteger(&anim_count, db, &data_pointer, file_size);
		std::cout << "0 / " << anim_count << "\n";
		for(int i = 0; i < anim_count; ++i)
		{
			dc_extractAnimation(&anim, db, &data_pointer, file_size);
			m_animations.push_back(anim);
			std::cout << i+1 << " / " << anim_count << "\n";
		}
	}

	// LOAD TEXTURES //////////////////////////////////////////////////////////
	if(COMPILE_TEXTURES)
	{
		std::cout << "Loading textures" << std::endl;
		int textures_count;
		dc_extractInteger(&textures_count, db, &data_pointer, file_size);
		std::cout << "0 / " << textures_count << "\n";
        for(int i = 0; i < textures_count; ++i)
		{
			file_info fi;
			dc_extractString(&(fi.file_name), db, &data_pointer, file_size);
			dc_extractString(&(fi.file_path), db, &data_pointer, file_size);
			dc_extractInteger(&(fi.file_size), db, &data_pointer, file_size);
			fi.data = new char[fi.file_size];
			for(int j = 0; j < fi.file_size; ++j)
			{
				dc_extractChar(&(fi.data[j]), db, &data_pointer, file_size);
			}
			m_textures.push_back(fi);
			std::cout << i+1 << " / " << textures_count << " : " << fi.file_name << "\n";
		}
	}

	// LOAD FONTS /////////////////////////////////////////////////////////////
	if(COMPILE_FONTS)
	{
		std::cout << "Loading fonts" << std::endl;
		int fonts_count;
		dc_extractInteger(&fonts_count, db, &data_pointer, file_size);
		std::cout << 0 << " / " << fonts_count << "\n";
        for(int i = 0; i < fonts_count; ++i)
		{
			file_info fi;
			dc_extractString(&(fi.file_name), db, &data_pointer, file_size);
			dc_extractString(&(fi.file_path), db, &data_pointer, file_size);
			dc_extractInteger(&(fi.file_size), db, &data_pointer, file_size);
			fi.data = new char[fi.file_size];
			for(int j = 0; j < fi.file_size; ++j)
			{
				dc_extractChar(&(fi.data[j]), db, &data_pointer, file_size);
			}
			m_fonts.push_back(fi);
			std::cout << i+1 << " / " << fonts_count << " : " << fi.file_name << "\n";
		}
	}

}

Data::~Data()
{
	if(m_ftc)
	{
		for(std::vector<TCreep*>::iterator it = m_tcreep.begin(); it != m_tcreep.end(); ++it)
		{
			delete *it;
		}
	}
	if(m_ftt)
	{
		for(std::vector<TTower*>::iterator it = m_ttower.begin(); it != m_ttower.end(); ++it)
		{
			delete *it;
		}
	}
	if(m_fan)
	{
		for(std::vector<Animation*>::iterator it = m_animations.begin(); it != m_animations.end(); ++it)
		{
			delete *it;
		}
	}
	if(m_fte)
	{
		for(std::vector<file_info>::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
		{
			delete [] (*it).data;
		}
	}
	if(m_ffo)
	{
		for(std::vector<file_info>::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
		{
			delete [] (*it).data;
		}
	}
	if(m_fmu)
	{
		for(std::vector<file_info>::iterator it = m_musics.begin(); it != m_musics.end(); ++it)
		{
			delete [] (*it).data;
		}
	}
	if(m_fso)
	{
		for(std::vector<file_info>::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
		{
			delete [] (*it).data;
		}
	}
}

bool Data::loadingState()
{
	return m_state;
}

std::vector<TCreep*> Data::getTCreeps()
{
	return m_tcreep;
}

std::vector<TTower*> Data::getTTowers()
{
	return m_ttower;
}

std::vector<Animation*> Data::getAnimations()
{
	return m_animations;
}

std::vector<file_info> Data::getTextures()
{
	return m_textures;
}

std::vector<file_info> Data::getFonts()
{
	return m_fonts;
}

std::vector<file_info> Data::getMusics()
{
	return m_musics;
}

std::vector<file_info> Data::getSounds()
{
	return m_sounds;
}

void Data::freeTCreeps()
{
	m_ftc = true;
}

void Data::freeTTowers()
{
	m_ftt = true;
}

void Data::freeAnimations()
{
	m_fan = true;
}

void Data::freeTextures()
{
	m_fte = true;
}

void Data::freeFonts()
{
	m_ffo = true;
}

void Data::freeMusics()
{
	m_fmu = true;
}

void Data::freeSounds()
{
	m_fso = true;
}



#endif // DATA_COMPILER
