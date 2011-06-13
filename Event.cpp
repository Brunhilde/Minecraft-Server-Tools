#include <iostream>
#include <string>
#include <ctime>

#include "UserManager.hpp"
#include "Event.hpp"

#include "Greet.hpp"

using namespace std;

void cEvent::playerConnected(const cUser& arg_user)
{
	cout<<"# "<<arg_user.getName()<<" ("<<arg_user.getIpAddress()<<") joined, time = "<<arg_user.getTimeConnected()<<endl;
	
	Greet->playerConnected(arg_user);
}


void cEvent::playerDisconnected(const cUser& arg_user)
{
	cout<<"# "<<arg_user.getName()<<" ("<<arg_user.getIpAddress()<<") disconnected, time = "<<arg_user.getTimeDisconnected()<<endl;
}