#ifndef __GREET_HPP
#define __GREET_HPP

#include "util/Singleton.hpp"
#include "User.hpp"

class cGreet : public cSingleton<cGreet>
{
public:
	void playerConnected(const cUser& arg_user);
};

#define Greet cGreet::getInstance()

#endif // __GREET_HPP