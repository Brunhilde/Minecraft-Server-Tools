#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>

#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>

#include "Config.hpp"

using namespace std;
namespace pod = boost::program_options::detail;

/* --------------------------------------------------------
	GLOBALS
   -------------------------------------------------------- */
const string g_sConfigFile = "mcsrv-tools.ini";

cConfig::cConfig()
{
}

cConfig::~cConfig()
{
}

void cConfig::init()
{
	read();
}

void cConfig::read()
{
	ifstream config(g_sConfigFile.c_str());
	
	if( !config )
	{
		cerr<<"Error: could not open config file '"<<g_sConfigFile<<"'"<<endl;
		exit(-1);
	}
	
	m_vOptions.insert("*");
	
	try
    {      
        for( pod::config_file_iterator it(config, m_vOptions), e ; it != e; ++it )
        {
            m_mParameters[it->string_key] = it->value[0];
        }
    }
    catch(std::exception& e)    
    {
        std::cerr<<"Exception: "<<e.what()<<std::endl;
    }
}

string cConfig::get(const string arg_param)
{
	return m_mParameters[arg_param];
}

string cConfig::get(const char* arg_param)
{
	return get(string(arg_param));
}