#include "../include/DataCompiler.hpp"
#include "../include/TDoodad.hpp"
#include <fstream>

std::vector<char>* mask;
int mask_pointer;
char control_sum;

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
	std::vector<TTower*> upgrades = tt->getUpgrades();
	Attack attack = tt->getAttack();
	Construction construction = tt->getConstruction();
	int construction_foundation_type = (int)(construction.foundation.type);
	if(!dc_compileInteger(&id, data_bloc, data_pointer, bloc_size))return false;
	if(!dc_compileString(&name, data_bloc, data_pointer, bloc_size))return false;
	for(uint32_t i = 0; i < upgrades.size(); ++i)
	{
		int uid = upgrades[i]->getId();
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
	data_bloc[*data_pointer] = t8c.ubyte & (*mask)[mask_pointer];
	control_sum = control_sum ^ t8c.schar;
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

#include <iomanip>
#include <dirent.h>

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

void bytetohex(int by, char* a, char* b)
{
	int va = (int)((by >> 4) & 0xf);
	int vb = (int)(by & 0xf);
	if(va > 9)*a = 'A' + (char)(va - 10);else *a = '0' + (char)(va);
	if(vb > 9)*b = 'A' + (char)(vb - 10);else *b = '0' + (char)(vb);
}

int main(int argc, char** argv)
{
	// Build mask
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
	int alloc_size = 5; // Reserve 4 bytes for data size and one byte for control sum;
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
		while(nullptr != (tc = TDoodad::getTCreep(ds.tc_count)))
		{
			++ds.tc_count;
			alloc_size += 28 + tc->getName().size();
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.tc_count << " - Allocation size:" << std::setfill(' ') << std::setw(10) << alloc_size << "\n";
		}
		std::cout << "Counting TTower elements..." << std::endl;
		while(nullptr != (tt = TDoodad::getTTower(ds.tt_count)))
		{
			++ds.tt_count;
			alloc_size += 40 + tt->getUpgrades().size() + (int)(UnitType::UNITTYPE_COUNT) + tt->getName().size();
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.tt_count << " - Allocation size:" << std::setfill(' ') << std::setw(10) << alloc_size << "\n";
		}
		std::cout << "Counting Animation elements..." << std::endl;
		while(nullptr != (anim = TDoodad::getAnimation(ds.anim_count)))
		{
			++ds.anim_count;
			alloc_size += 32 + anim->getName().size();
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.anim_count << " - Allocation size:" << std::setfill(' ') << std::setw(10) << alloc_size << "\n";
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
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << count_textures << " - Allocation size:" << std::setfill(' ') << std::setw(10) << alloc_size << "\n";
		}
		if (-1 == closedir(rep))
		{
			std::cerr << "Error when closing directory \"" << SHARE_DIR << "/texture\"" << std::endl;
			return dc_error();
		}
	}

	// CREATE DATA ////////////////////////////////////////////////////////////
	std::cout << "Allocating data bloc" << std::endl;
	data_byte db = new char[alloc_size];
	int data_pointer = 0;
	dc_compileInteger(&alloc_size, db, &data_pointer, alloc_size); // Save size

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
		while(nullptr != (tc = TDoodad::getTCreep(ds.tc_count)))
		{
			++ds.tc_count;
			dc_compileCreep(tc, db, &data_pointer, alloc_size);
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.tc_count << " / " << tmp << "\n";
		}
		dc_compileInteger(&(ds.tt_count), db, &data_pointer, alloc_size);
		tmp = ds.tt_count;
		ds.tt_count = 0;
		std::cout << "Compiling TTower elements..." << std::endl;
		while(nullptr != (tt = TDoodad::getTTower(ds.tt_count)))
		{
			++ds.tt_count;
			dc_compileTower(tt, db, &data_pointer, alloc_size);
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.tt_count << " / " << tmp << "\n";
		}
		dc_compileInteger(&(ds.anim_count), db, &data_pointer, alloc_size);
		tmp = ds.anim_count;
		ds.anim_count = 0;
		std::cout << "Compiling Animation elements..." << std::endl;
		while(nullptr != (anim = TDoodad::getAnimation(ds.anim_count)))
		{
			++ds.anim_count;
			dc_compileAnimation(anim, db, &data_pointer, alloc_size);
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << ds.anim_count << " / " << tmp << "\n";
		}
	}

	// SAVE TEXTURES //////////////////////////////////////////////////////////
	if(COMPILE_TEXTURES)
	{
		std::cout << "Compiling textures" << std::endl;
		int s = ds.texture_files.size();
		dc_compileInteger(&s, db, &data_pointer, alloc_size);
		std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << 0 << " / " << s << "\n";
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
			std::cout << "Elements: " << std::setfill(' ') << std::setw(10) << i << " / " << s << "\n";
		}
	}

	// SAVE FILE //////////////////////////////////////////////////////////////
	db[data_pointer] = control_sum; // Add ckecksum (one byte)
	std::cout << "\nSaving file..." << std::endl;
	dc_exportData(DATA_DIR"data.bin", db, alloc_size);
	delete [] db;
	std::cout << "done !" << std::endl;
	system("PAUSE");
	return 0;
}

#endif // DATA_COMPILER
