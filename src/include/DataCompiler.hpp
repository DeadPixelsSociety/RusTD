#ifndef DATACOMPILER_HPP
#define DATACOMPILER_HPP

#ifdef DATA_COMPILER

#include "TCreep.hpp"
#include "TTower.hpp"
#include "Animation.hpp"
#include "config.hpp"


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

uint8_t getByte(uint32_t uinteger, int b0_to_3);
uint32_t setByte(uint32_t uinteger, int b0_to_3, uint8_t b);
uint8_t getByte(int32_t integer, int b0_to_3);
int32_t setByte(int32_t integer, int b0_to_3, uint8_t b);
uint8_t getByte(float real, int b0_to_3);
float setByte(float real, int b0_to_3, uint8_t b);
uint8_t getByte(type32_converter tc, int b0_to_3);
type32_converter setByte(type32_converter tc, int b0_to_3, uint8_t b);

typedef char* data_byte;

bool dc_compileCreep(TCreep* tc, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileTower(TTower* tt, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileAnimation(Animation* anim, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileString(const std::string& value, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileInteger(int value, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileFloat(float value, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_compileChar(char value, data_byte* data_bloc, int* data_pointer, int bloc_size);

bool dc_exportData(const std::string& filename, data_byte* data_bloc, int bloc_size);

#endif

#endif // DATACOMPILER_HPP
