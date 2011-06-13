#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "Server.hpp"
#include "Config.hpp"

using namespace std;

cServer::cServer()
{
}

cServer::~cServer()
{
}

void cServer::init()
{
	//say("Minecraft-Server-Tools now starting...");
}

void cServer::cmd(const string arg_cmd)
{
	stringstream str;
	
	str<<"screen -S "<<Config->get("Server.Screen")<<" -p 0 -X stuff \"`printf \""<<arg_cmd<<"\r\"`\"";
	system(str.str().c_str());
}

void cServer::say(const string arg_text)
{
	stringstream str;
	
	str<<"say "<<arg_text;
	cmd(str.str());
}