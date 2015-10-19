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
#ifndef __RANDOM_HPP
#define __RANDOM_HPP

#include <chrono>
#include <random>

class Random
{
public:

	virtual ~Random(void);

	static int NextInt(int base, int limit);

	static int NextInt(void);

	static float NextFloat(float base, float limit);

	static float NextFloat(void);

	static double NextDouble(double base, double limit);

	static double NextDouble(void);

	static char NextChar(char base, char limit);

	static char NextChar(void);

	static bool NextBool(void);

	static long NextLong(long base, long limit);

	static long NextLong(void);

	static short NextShort(short base, short limit);

	static short NextShort(void);

	static uint64_t GetSeed(void);

	static void SetSeed(uint64_t seed);

protected:

	explicit Random(void);

	explicit Random(uint64_t seed);

	std::mt19937 m_generator;

	uint64_t m_seed;

	static Random s_instance;

private:

};

#endif // __RANDOM_HPP
