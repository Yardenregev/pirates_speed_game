
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ~/projects

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = $(MY_PROJ_DIR)/src/$(wildcard *.cpp) pirates_speed_game/test/commander_captain_test.cpp

# list of directories containing header files
PROJ_INC_DIR = pirates_speed_game/include pirates_speed_game/include/design_patterns

# the executable file
PROJ_OUT = a.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =
PROJ_CPPFLAGS = -std=c++11

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  =

include $(ROOT_DIR)/make/Project.mak
