#include <vector>
#include <sstream>

#include "Greet.hpp"
#include "Server.hpp"
#include "UserManager.hpp"

using namespace std;

void cGreet::playerConnected(const cUser& arg_user)
{
	stringstream str;
	vector<cUser> vUsers = UserManager->usersGetConnected();
	
	str<<"Hey "<<arg_user.getName();
	Server->say(str.str());	
	Server->say("-------------------------");
	Server->say("Currently connected players:");
	
	for( vector<cUser>::iterator it = vUsers.begin() ; it != vUsers.end() ; ++it )
	{
		str.str(string()); // empty stringstream
		
		str<<"- "<<it->getName()<<" (since "<<it->getTimeConnected()<<", overall "<<it->getTimeOverall()<<")";
		Server->say(str.str());
	}
}