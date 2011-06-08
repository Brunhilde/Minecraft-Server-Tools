#ifndef __SERVER_HPP
#define __SERVER_HPP

#include "util/Singleton.hpp"

class cServer : public cSingleton<cServer>
{
public:
	cServer();
	~cServer();
	
	void init();
	
	void cmd(std::string arg_cmd);
	
private:
};

#define Server cServer::getInstance()

#endif // __SERVER_HPP