#ifndef __CONIFG_HPP
#define __CONFIG_HPP

#include <string>
#include <set>
#include <map>

#include "util/Singleton.hpp"

class cConfig : public cSingleton<cConfig>
{
public:
	cConfig();
	~cConfig();
	
	void init();
	
	void read();
	std::string get(const std::string arg_param);
	std::string get(const char* arg_param);

private:
	std::set<std::string>              m_vOptions;
	std::map<std::string, std::string> m_mParameters;
};

#define Config cConfig::getInstance()

#endif // __CONFIG_HPP