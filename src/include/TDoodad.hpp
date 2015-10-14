#ifndef TDOODAD_H
#define TDOODAD_H

#include "TTower.hpp"
#include "TCreep.hpp"

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

protected:
	static std::vector<TTower*> m_ttower;
	static std::vector<TCreep*> m_tcreep;

private:
	TDoodad(void);
};

#endif
