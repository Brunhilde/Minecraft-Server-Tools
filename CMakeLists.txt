project(MinecraftServerTools)

set(mcsrv-tools-src
	main.cpp
	Config.cpp
	Server.cpp
	LogParser.cpp
	UserManager.cpp
	User.cpp
	Event.cpp
	Greet.cpp
)
set(mcsrv-tools-libs
	pthread

	soci_core
	soci_sqlite3

	boost_program_options
)

add_executable(mcsrv-tools ${mcsrv-tools-src})
target_link_libraries(mcsrv-tools ${mcsrv-tools-libs})
