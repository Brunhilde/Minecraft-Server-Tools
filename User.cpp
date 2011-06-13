#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include "User.hpp"

using namespace std;
using namespace soci;

extern session db;

cUser UserInvalid("Invalid");

cUser::cUser()
{
}

cUser::cUser(std::string arg_name)
: m_sName(arg_name)
{
}

cUser::~cUser()
{
}

void cUser::addToDb(void)
{
}

void cUser::updateDb(void)
{
}