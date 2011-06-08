#ifndef __USER_HPP
#define __USER_HPP

#include <string>
#include <time.h>

class cUser
{
public:
	cUser();
	~cUser();
	
	std::string m_sName;
	std::string m_sIpAddress;
	time_t      m_tJoined;
	time_t      m_tDisconnected;
	time_t      m_tOverall;
	
private:
	
}; 

#endif // __USER_HPP