#ifndef __USERMANAGER_HPP
#define __USERMANAGER_HPP

#include <time.h>

#include "util/Singleton.hpp"
#include "User.hpp"

class cUserManager : public cSingleton<cUserManager>
{
public:
	cUserManager();
	~cUserManager();
	
	void init();
	
	void usersSync();
	
	cUser& userGetByName(std::string arg_name);
	cUser& userGetByIPAddress(std::string arg_ipaddress);
	void   userAdd(std::string arg_name, std::string arg_ipaddress, time_t arg_timejoined);
	void   userUpdate(cUser& arg_user);
	
private:
	void checkTables();
	
	std::vector<cUser>  m_vUsers;
	std::vector<cUser*> m_vUsersConnected;
};

#define UserManager cUserManager::getInstance()

#endif // __USERMANAGER_HPP