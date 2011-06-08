#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include "UserManager.hpp"

using namespace std;
using namespace soci;

extern session db;

cUserManager::cUserManager()
{
	checkTables();
}

cUserManager::~cUserManager()
{
}

void cUserManager::init()
{
}

void cUserManager::usersSync()
{
}

cUser& cUserManager::userGetByName(std::string arg_name)
{
}

cUser& cUserManager::userGetByIPAddress(std::string arg_ipaddress)
{
}

void cUserManager::userAdd(std::string arg_name, std::string arg_ipaddress, time_t arg_timejoined)
{
}

void cUserManager::userUpdate(cUser& arg_user)
{
}

void cUserManager::checkTables()
{
	cout<<"Checking database tables..."<<endl;
	
	try
	{
		cout<<"1/1 ... users"<<endl;
		db<<" \
			CREATE TABLE IF NOT EXISTS \
				users \
			( \
				id                  INTEGER PRIMARY KEY AUTOINCREMENT, \
				name                TEXT, \
				ipaddress           TEXT, \
				time_lastjoin       INTEGER, \
				time_lastdisconnect INTEGER, \
				time_overall        INTEGER \
			); \
		";
	}
	catch(exception const  &e)
	{
		cerr<<"Error: "<<e.what()<<endl;
	}
	
	cout<<"... all tables checked"<<endl;
}