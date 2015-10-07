#ifndef TDOODAD_H
#define TDOODAD_H

#include "TTower.hpp"
#include "TCreep.hpp"

class TDoodad
{
public:
	TDoodad(void);

	~TDoodad(void);

	void load_XML(void);
	void load_towerXML(std::string path_file);
	void load_creepXML(std::string path_file);

protected:
	std::vector<TTower*> m_ttower;
	std::vector<TCreep*> m_tcreep;

};

#endif
