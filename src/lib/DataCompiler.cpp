#ifdef DATA_COMPILER

#include "../include/DataCompiler.hpp"
#include <fstream>

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

void setByte(type32_converter tc, int b0_to_3, uint8_t b)
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
		return 0;
	}
}

bool dc_compileCreep(TCreep* tc, data_byte* data_bloc, int* data_pointer, int bloc_size)
{

	return true;
}

bool dc_compileTower(TTower* tt, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	return true;
}

bool dc_compileAnimation(Animation* anim, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	return true;
}

bool dc_compileString(const std::string& value, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4 + value.size())return false;
	type32_converter tc;
	tc.uinteger = value.size();
	if(!dc_compileInteger(tc.integer, data_bloc, data_pointer, bloc_size))return false;
	for(uint32_t = 0; i < tc.uinteger; ++i)
	{
		if(!dc_compileChar(value[i], data_bloc, data_pointer, bloc_size))return false;
	}
	return true;
}

bool dc_compileInteger(int value, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4)return false;
	type32_converter t32c;
	t32c.integer = value;
	type8_converter t8c;
	t8c.ubyte = getByte(value, 0);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 1);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 2);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 3);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileFloat(float value, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 4)return false;
	type32_converter t32c;
	t32c.real = value;
	type8_converter t8c;
	t8c.ubyte = getByte(value, 0);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 1);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 2);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	t8c.ubyte = getByte(value, 3);
	if(!dc_compileChar(t8c.byte, data_bloc, data_pointer, bloc_size))return false;
	return true;
}

bool dc_compileChar(char value, data_byte* data_bloc, int* data_pointer, int bloc_size)
{
	if(bloc_size <= *data_pointer + 1)return false;
	type8_converter t8c;
	t8c.byte = value;
	data_bloc[*data_pointer] = t8c.ubyte;
	++(*data_pointer);
	return true;
}

bool dc_exportData(const std::string& filename, data_byte* data_bloc, int bloc_size)
{
	std::ofstream out(filename.c_str(), std::ios::out | std::ios::binary);
	out.open();
	if(!out.good() || !out.is_open())return false;
	out.write(data_bloc, bloc_size);
	out.close();
}

#endif // DATA_COMPILER
