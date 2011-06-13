#ifndef __USERMANAGER_HPP
#define __USERMANAGER_HPP

#include <vector>

#include <ctime>

#include "util/Singleton.hpp"
#include "User.hpp"

class cUserManager : public cSingleton<cUserManager>
{
public:
	cUserManager();
	~cUserManager();
	
	void init();
	
	void usersSync();
	
	cUser userGetByName(const std::string arg_name);
	cUser userGetByIPAddress(const std::string arg_ipaddress);
	const std::vector<cUser>& usersGetConnected() const;
	
	cUser userAdd(const std::string arg_name, const std::string arg_ipaddress, const time_t arg_timejoined, const time_t arg_timedisconnected, const time_t arg_timeoverall);
	void  userUpdate(const cUser& arg_user);
	
	cUser userConnected(const std::string arg_name, const std::string arg_ipaddress, const time_t arg_timejoined);
	cUser userDisconnected(const std::string arg_name, const time_t arg_timedisconnected);
	
private:
	void checkTables();
	bool userExists(const std::string arg_name);
	void usersGetAll();
	
	std::vector<cUser>  m_vUsers;
	std::vector<cUser>  m_vUsersConnected;
};

#define UserManager cUserManager::getInstance()

#endif // __USERMANAGER_HPP