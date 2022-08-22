CXX = g++
CXXFLAGS = -pthread

PROJ_SRCS = $(wildcard src/*.cpp) ./include/pirate_types/pirate_types.cpp

PROJ_INCLUDES = -I./include/

all:
	make commander && make captain

commander:
	$(CXX) $(CXXFLAGS) $(PROJ_INCLUDES) $(PROJ_SRCS) executables/commander_exec.cpp -o commander.out

captain:
	$(CXX) $(CXXFLAGS) $(PROJ_INCLUDES) $(PROJ_SRCS) executables/captain_exec.cpp -o captain.out


clean:
	rm *.out


