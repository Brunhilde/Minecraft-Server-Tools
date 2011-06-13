#ifndef __LOGPARSER_HPP
#define __LOGPARSER_HPP

#include<string>
#include<queue>

#include "util/Singleton.hpp"

class cLogParser : public cSingleton<cLogParser>
{
public:
	cLogParser();
	~cLogParser();
	
	// Accessors
	void setFileName(const std::string arg_filename) { m_sFileName = arg_filename; }
	
	void init();
	int tail();
	
	void cyclic();

private:
	int parse();
	
	void handleLine(const std::string arg_line);
	std::string extractIpAddress(const std::string arg_ipaddress);
	
	std::string m_sFileName;
	
	std::queue<std::string> m_qReadLines;
};

#define LogParser cLogParser::getInstance()

#endif // __LOGPARSER_HPP

