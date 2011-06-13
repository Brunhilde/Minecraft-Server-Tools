#ifndef __USER_HPP
#define __USER_HPP

#include <string>
#include <ctime>

class cUserManager;

class cUser
{
public:
	cUser();
	cUser(std::string arg_name);
	~cUser();
	
	cUser& getReference(void) { return *this; };
	
	std::string getName(void) const             { return m_sName;         };
	std::string getIpAddress(void) const        { return m_sIpAddress;    };
	time_t      getTimeConnected(void) const    { return m_tConnected;    };
	time_t      getTimeDisconnected(void) const { return m_tDisconnected; };
	time_t      getTimeOverall(void) const      { return m_tOverall;      };
	
private:
	void setName(const std::string arg_name)                    { m_sName = arg_name;                     };
	void setIpAddress(const std::string arg_ipaddress)          { m_sIpAddress = arg_ipaddress;           };
	void setTimeConnected(const time_t arg_timeconnected)       { m_tConnected = arg_timeconnected;       };
	void setTimeDisconnected(const time_t arg_timedisconnected) { m_tDisconnected = arg_timedisconnected; };
	void setTimeOverall(const time_t arg_timeoverall)           { m_tOverall = arg_timeoverall;           };
	
	void addToDb ();
	void updateDb();

	std::string  m_sName;
	std::string  m_sIpAddress;
	time_t       m_tConnected;
	time_t       m_tDisconnected;
	time_t       m_tOverall;	
	
	friend class cUserManager;
}; 

extern cUser UserInvalid;

#endif // __USER_HPP