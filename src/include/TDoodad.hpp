#ifndef TDOODAD_H
#define TDOODAD_H

#include "TTower.hpp"
#include "TCreep.hpp"

class TDoodad
{
public:
	~TDoodad(void);

	static bool load_XML(std::string& share_path);
	static bool load_towerXML(std::string& tower_path);
	static bool load_towerFile(std::string& tower_file_path);
	static bool load_creepXML(std::string& creep_path);
	static bool load_creepFile(std::string& creep_file_path);
	static void destroy_objects();

    static TTower* getTower(int i);

protected:
	static std::vector<TTower*> m_ttower;
	static std::vector<TCreep*> m_tcreep;

private:
	TDoodad(void);
};

#endif
