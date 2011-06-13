#ifndef __EVENT_HPP
#define __EVENT_HPP

#include "util/Singleton.hpp"

#include "User.hpp"

class cEvent : public cSingleton<cEvent>
{
public:
	void playerConnected   (const cUser& arg_user);
	void playerDisconnected(const cUser& arg_user);

private:
};

#define Event cEvent::getInstance()

#endif // __EVENT_HPP