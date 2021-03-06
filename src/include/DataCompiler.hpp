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
#ifndef DATACOMPILER_HPP
#define DATACOMPILER_HPP

#include "TCreep.hpp"
#include "TTower.hpp"
#include "Animation.hpp"
#include "config.hpp"
#include <vector>

#define CRYPT_KEY "RusTD"

#define COMPILE_UNITS true
#define COMPILE_TEXTURES true
#define COMPILE_FONTS true
#define COMPILE_MUSICS false
#define COMPILE_SOUNDS false

#define HIDE_DATA

union type32_converter
{
	uint32_t uinteger;
	int32_t integer;
	float real;
};

union type8_converter
{
	uint8_t ubyte;
	int8_t byte;
	unsigned char uchar;
	char schar;
};

struct byte_set
{
	uint8_t byte0;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
};

union byte_accessor
{
	type32_converter value;
	byte_set bytes;
};

struct file_info
{
	file_info():file_name(""),file_path(""),file_size(0),data(nullptr){}
	std::string file_name;
	std::string file_path;
	int file_size;
	char* data;
};

struct data_save
{
	data_save()
	: tc_count(0)
	, tt_count(0)
	, anim_count(0)
	{}
	int tc_count;
	int tt_count;
	int anim_count;
	std::vector<file_info> texture_files;
	std::vector<file_info> font_files;
	std::vector<file_info> music_files;
	std::vector<file_info> sound_files;
};

uint8_t getByte(uint32_t uinteger, int b0_to_3);
uint32_t setByte(uint32_t uinteger, int b0_to_3, uint8_t b);
uint8_t getByte(int32_t integer, int b0_to_3);
int32_t setByte(int32_t integer, int b0_to_3, uint8_t b);
uint8_t getByte(float real, int b0_to_3);
float setByte(float real, int b0_to_3, uint8_t b);
uint8_t getByte(type32_converter tc, int b0_to_3);
type32_converter setByte(type32_converter tc, int b0_to_3, uint8_t b);

int dc_error(void);

typedef char* data_byte;

#ifdef DATA_COMPILER // Define this only if no other main are defined

/*
	To compile DataCompiler, create a new compilation target defining DATA_COMPILER
	This target must include following files :
	- Animation.hpp & Animation.cpp
	- config.hpp
	- TCreep.hpp & TCreep.cpp
	- TDoodad.hpp & TDoodad.cpp
	- tinyxml2.h & tinyxml2.cpp
	- TTower.hpp & TTower.cpp
	The target must be linked with at least sfml-graphics, sfml-window and sfml-system
*/
bool dc_compileCreep(TCreep* tc, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileTower(TTower* tt, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileAnimation(Animation* anim, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileString(std::string* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileInteger(int* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileFloat(float* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_compileChar(char* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_exportData(const std::string& filename, data_byte data_bloc, int bloc_size);

#else

bool dc_extractCreep(TCreep* tc, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractTower(TTower* tt, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractAnimation(Animation* anim, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractString(std::string* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractInteger(int* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractFloat(float* value, data_byte data_bloc, int* data_pointer, int bloc_size);
bool dc_extractChar(char* value, data_byte data_bloc, int* data_pointer, int bloc_size);

class Data
{
public:
	Data(const std::string& filename);
	~Data(void);

	bool loadingState();

	std::vector<TCreep*> getTCreeps(void);
	std::vector<TTower*> getTTowers(void);
	std::vector<Animation*> getAnimations(void);
	std::vector<file_info> getTextures(void);
	std::vector<file_info> getFonts(void);
	std::vector<file_info> getMusics(void);
	std::vector<file_info> getSounds(void);

	void freeTCreeps(void);
	void freeTTowers(void);
	void freeAnimations(void);
	void freeTextures(void);
	void freeFonts(void);
	void freeMusics(void);
	void freeSounds(void);

protected:

	int m_state;

	bool m_ftc, m_ftt, m_fan, m_fte, m_ffo, m_fmu, m_fso;

	std::vector<TCreep*> m_tcreep;
	std::vector<TTower*> m_ttower;
	std::vector<Animation*> m_animations;
	std::vector<file_info> m_textures;
	std::vector<file_info> m_fonts;
	std::vector<file_info> m_musics;
	std::vector<file_info> m_sounds;

};

#endif

#endif // DATACOMPILER_HPP
