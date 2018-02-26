# Path to the directory where `ecdboost` is placed
LIB_DIR = ../../..
# Path to ecdboost buitlins
BUILTIN_DIR = $(LIB_DIR)/ecdboost/builtins
# Path to the boost library
BOOST_DIR = /home/bitcraze/projects/boost_1_57_0

INCLUDES = -I$(BOOST_DIR) -I$(LIB_DIR)
DEFINES = -DENABLE_SIMULATION
CPP_FILES = src/main.cpp $(BUILTIN_DIR)/linux_timer.cpp

all:
	g++ $(DEFINES) $(INCLUDES) -fpermissive -std=c++11 $(CPP_FILES) -o test.bin

clean:
	rm test.bin output.txt

