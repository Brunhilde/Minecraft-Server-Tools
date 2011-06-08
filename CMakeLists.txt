project(MinecraftServerTools)

set(mcsrv-tools-src
	main.cpp
	LogParser.cpp
)
set(mcsrv-tools-libs
	pthread
)

add_executable(mcsrv-tools ${mcsrv-tools-src})
target_link_libraries(mcsrv-tools ${mcsrv-tools-libs})
