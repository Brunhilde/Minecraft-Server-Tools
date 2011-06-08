#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include "LogParser.hpp"
#include "User.hpp"

using namespace std;
using namespace soci;


/* --------------------------------------------------------
	GLOBALS
   -------------------------------------------------------- */
const char g_sVersion[] = "0.1";
   
session db(sqlite3, "mcsrv-tools.db");


/* --------------------------------------------------------
	PROTOTYPES
   -------------------------------------------------------- */
void *readThreadFunc(void* arg);


/* --------------------------------------------------------
	FUNCIONS
   -------------------------------------------------------- */
int main(int argc, char **argv)
{
	bool bRunning = true;
	pthread_t readThread;
	cUser user;
	
	cout<<"Minecraft-Server-Tools v"<<g_sVersion<<endl;
	
	cLogParser::getInstance()->setFileName("/home/minecraft/minecraft-server/server.log");
	
	pthread_create( &readThread, NULL, readThreadFunc, NULL );
	
	while(bRunning)
	{
		cLogParser::getInstance()->parse();
		usleep(200 * 1000);
	}

	return 0;
}

void *readThreadFunc(void* arg)
{
	cLogParser::getInstance()->tail();
}
