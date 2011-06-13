#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include "Config.hpp"
#include "Server.hpp"
#include "LogParser.hpp"
#include "UserManager.hpp"

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
	string sLogFile;
	
	cout<<"Minecraft-Server-Tools v"<<g_sVersion<<endl
		<<endl;
	
	// ----------------------------------------------------
	Config->init();
	Server->init();
	LogParser->init();
	UserManager->init();
	
	// ----------------------------------------------------
	sLogFile = Config->get("Minecraft.Path") + "/" + Config->get("Minecraft.LogFile");
	LogParser->setFileName(sLogFile);
	
	pthread_create( &readThread, NULL, readThreadFunc, NULL );
	
	while(bRunning)
	{
		LogParser->cyclic();
		usleep(100 * 1000);
	}

	return 0;
}

void *readThreadFunc(void* arg)
{
	LogParser->tail();
}
