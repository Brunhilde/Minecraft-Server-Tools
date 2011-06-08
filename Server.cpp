#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "Server.hpp"

using namespace std;

cServer::cServer()
{
}

cServer::~cServer()
{
}

void cServer::init()
{
	//cmd("say Minecraft-Server-Tools now starting...");
}

void cServer::cmd(string arg_cmd)
{
	stringstream str;
	
	str<<"screen -S mcsrv -p 0 -X stuff \"`printf \""<<arg_cmd<<"\r\"`\"";
	
	system(str.str().c_str());
}