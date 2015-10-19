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
#include "../include/Random.hpp"

/*explicit*/ Random::Random()
{
	m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	m_generator.seed(m_seed);
}

/*explicit*/ Random::Random(uint64_t seed)
{
	m_seed = seed;
	m_generator.seed(m_seed);
}

/*virtual*/ Random::~Random()
{

}

/*static*/ int Random::NextInt(int base, int limit)
{
	std::uniform_int_distribution<int> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ int Random::NextInt()
{
	return NextInt(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

/*static*/ float Random::NextFloat(float base, float limit)
{
	std::uniform_real_distribution<float> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ float Random::NextFloat()
{
	return NextFloat(std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
}

/*static*/ double Random::NextDouble(double base, double limit)
{
	std::uniform_real_distribution<double> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ double Random::NextDouble()
{
	return NextDouble(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());
}

/*static*/ char Random::NextChar(char base, char limit)
{
	std::uniform_int_distribution<char> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ char Random::NextChar()
{
	return NextChar(std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
}

/*static*/ bool Random::NextBool()
{
	return (0 == NextInt(0, 1));
}

/*static*/ long Random::NextLong(long base, long limit)
{
	std::uniform_int_distribution<long> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ long Random::NextLong()
{
	return NextLong(std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
}

/*static*/ short Random::NextShort(short base, short limit)
{
	std::uniform_int_distribution<short> out(base, limit);
	return out(s_instance.m_generator);
}

/*static*/ short Random::NextShort()
{
	return NextShort(std::numeric_limits<short>::min(), std::numeric_limits<short>::max());
}

/*static*/ uint64_t Random::GetSeed()
{
	return s_instance.m_seed;
}

/*static*/ void Random::SetSeed(uint64_t seed)
{
	s_instance.m_seed = seed;
	s_instance.m_generator.seed(s_instance.m_seed);
}

/*static*/ Random Random::s_instance;
