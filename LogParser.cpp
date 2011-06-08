#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <fstream>

#include <sys/inotify.h>

#include "LogParser.hpp"
#include "Events.hpp"

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
			
			cout<<line<<endl;
	}
}

void cLogParser::cyclic()
{
}
