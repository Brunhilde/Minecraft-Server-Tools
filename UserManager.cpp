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
	usersGetAll();
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

cUser cUserManager::userGetByName(const std::string arg_name)
{
	for( vector<cUser>::iterator it = m_vUsers.begin() ; it != m_vUsers.end() ; ++it )
	{
		if( it->getName().compare(arg_name) == 0 )
			return *it;
	}
	
	return UserInvalid;
}

cUser cUserManager::userGetByIPAddress(const std::string arg_ipaddress)
{
	for( vector<cUser>::iterator it = m_vUsers.begin() ; it != m_vUsers.end() ; ++it )
	{
		if( it->getIpAddress().compare(arg_ipaddress) == 0 )
			return *it;
	}
	
	return UserInvalid;
}

const std::vector<cUser>& cUserManager::usersGetConnected() const
{
	return m_vUsersConnected;
}

cUser cUserManager::userAdd(const string arg_name, const string arg_ipaddress = "", const time_t arg_timejoined = 0, const time_t arg_timedisconnected = 0, const time_t arg_timeoverall = 0)
{	
	cUser user;
	
	try
	{
		db<<" \
			INSERT INTO \
				users \
			(name, ipaddress, time_lastjoin) \
			VALUES( \
				:name, \
				:ipaddress, \
				:time \
			); \
		",
		use(arg_name),
		use(arg_ipaddress),
		use((int)arg_timejoined);
		
		user.setName            (arg_name);
		user.setIpAddress       (arg_ipaddress);
		user.setTimeConnected   (arg_timejoined);
		user.setTimeDisconnected(arg_timedisconnected);
		user.setTimeOverall     (arg_timeoverall);
		
		m_vUsers.push_back(user);
	}
	catch(exception const& e)
	{
		cerr<<"Error: "<<e.what()<<endl;
		
		user = UserInvalid;
	}
	
	return user;
}

void cUserManager::userUpdate(const cUser& arg_user)
{
	try
	{
		db<<"UPDATE users SET name=:name, ipaddress=:ipaddress, time_lastjoin=:timejoin, time_lastdisconnect=:timedisconnect, time_overall=:timeoverall WHERE name=:thename",
			use(arg_user.getName()), use(arg_user.getIpAddress()), use((int)arg_user.getTimeConnected()), use((int)arg_user.getTimeDisconnected()), use((int)arg_user.getTimeOverall()), use(arg_user.getName());
	}	
	catch(exception const& e)
	{
		cerr<<"Error: "<<e.what()<<endl;
	}	
}

bool cUserManager::userExists(const string arg_name)
{
	bool userFound = false;
	int count      = 0;
	
	try
	{
		db<<"SELECT COUNT(id) FROM users WHERE name=:name", into(count), use(arg_name);
		
		if( count != 0 )
			userFound = true;
	}
	catch(exception const& e)
	{
		cerr<<"Error: "<<e.what()<<endl;
	}
	
	return userFound;
}

cUser cUserManager::userConnected(const std::string arg_name, const std::string arg_ipaddress, const time_t arg_timejoined)
{
	cUser user;
	
	if( !userExists(arg_name) )
	{
		user = userAdd(arg_name, arg_ipaddress, arg_timejoined);
	}
	else
	{
		user = userGetByName(arg_name);
		
		// update connect time
		user.setTimeConnected(time(NULL));
		userUpdate(user);
	}
	
	m_vUsersConnected.push_back(user);
	
	cout<<"Users connected: "<<m_vUsersConnected.size()<<endl;
	
	return user;
}

cUser cUserManager::userDisconnected(const std::string arg_name, const time_t arg_timedisconnected)
{
	cUser user;

	if( !userExists(arg_name) )
	{
		user = userAdd(arg_name, "", 0, arg_timedisconnected);
	}
	else
	{
		user = userGetByName(arg_name);
		
		// Update times
		user.setTimeDisconnected(arg_timedisconnected);
		user.setTimeOverall     ( user.getTimeOverall() + (user.getTimeDisconnected() - user.getTimeConnected()) );
		userUpdate(user);
	}
	
	for( vector<cUser>::iterator it = m_vUsersConnected.begin() ; it != m_vUsersConnected.end() ; ++it )
	{
		if( it->getName().compare(arg_name) == 0 )
		{
			m_vUsersConnected.erase(it);
			
			break;
		}
	}
	
	cout<<"Users connected: "<<m_vUsersConnected.size()<<endl;
	
	return user;
}

void cUserManager::usersGetAll()
{
	cUser user;
	
	try
	{
		rowset<row> rs = ( db.prepare<<"SELECT name, ipaddress, time_lastjoin, time_lastdisconnect, time_overall FROM users" );
		
		for( rowset<row>::const_iterator it = rs.begin() ; it != rs.end() ; ++it )
		{			
			user.setName            ( it->get<string>(0, "Invalid") );
			user.setIpAddress       ( it->get<string>(1, "None") );
			user.setTimeConnected   ( static_cast<time_t>(it->get<int>(2, 0)) );
			user.setTimeDisconnected( static_cast<time_t>(it->get<int>(3, 0)) );
			user.setTimeOverall     ( static_cast<long int>(it->get<int>(4, 0)) );
			
			m_vUsers.push_back(user);
		}
	}
	catch(exception const& e)
	{
		cerr<<"Error: "<<e.what()<<endl;
	}
	
	cout<<"Fetched "<<m_vUsers.size()<<" user(s) from database"<<endl;
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
	catch(exception const& e)
	{
		cerr<<"Error: "<<e.what()<<endl;
	}
	
	cout<<"... all tables checked"<<endl;
}