#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <fstream>

#include <sys/inotify.h>
#include <ctime>

#include "LogParser.hpp"
#include "Event.hpp"
#include "UserManager.hpp"
#include "User.hpp"

using namespace std;

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

cLogParser::cLogParser()
{
}

cLogParser::~cLogParser()
{
}

void cLogParser::init()
{
}

int cLogParser::tail()
{
	ifstream in(m_sFileName.c_str(), ios::in | ios::ate);
	string line;
	int fd;
	int wd;
	int len;
	char buf[BUF_LEN];
	
	fd = inotify_init();
	wd = inotify_add_watch( fd, m_sFileName.c_str(), IN_MODIFY | IN_CREATE );
	
	if( !in )
	{
		cerr<<"Error: could not open log file '"<<m_sFileName<<"'"<<endl;
		exit(-1);
	}
	
	while(1)
	{		
		while( !in.eof() )
		{
			getline(in, line);
			if(line.length() > 1)
				m_qReadLines.push( line );
		}
		
		len = read( fd, buf, BUF_LEN );
		if( len < 0 )
			perror("read");
		
		if( !in.good() )
			in.clear();
	}
}

int cLogParser::parse()
{
	string line;
	
	while( !m_qReadLines.empty() )
	{
		line = m_qReadLines.front();
		m_qReadLines.pop();
		handleLine(line);
			
		//cout<<line<<endl;
	}
}

void cLogParser::handleLine(const std::string arg_line)
{
	stringstream   line;
	vector<string> parts;
	string         temp;
	
	cUser          user;
	string		   name;
	string         ipaddress;
	time_t         now;
	
	
	line<<arg_line;
	
	while( getline(line, temp, ' ') )	
		parts.push_back(temp);
		
	// valid lines have more than 3 parts
	if( parts.size() <= 3 )
		return;
		
	// check for login
	if( arg_line.find("logged in") != string::npos )
	{	
		name      = parts[3];
		ipaddress = extractIpAddress(parts[4]);
		now       = time(NULL);
		
		user = UserManager->userConnected(name, ipaddress, now);
		Event->playerConnected(user);		
	}
	
	// check for disconnect
	else if( arg_line.find("lost connection") != string::npos )
	{
		name = parts[3];
		now  = time(NULL);
		
		user = UserManager->userDisconnected(name, now);
		Event->playerDisconnected(user);
	}
}

string cLogParser::extractIpAddress(const string arg_ipaddress)
{
	string ipaddress;
	
	// [/ip:port]
	// extract: ip:port
	ipaddress.assign( arg_ipaddress.begin()+2, arg_ipaddress.begin()+(int)arg_ipaddress.find("]") );
	
	return ipaddress;
}


void cLogParser::cyclic()
{
	parse();
}
