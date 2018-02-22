LIBDIR = ../../..
BUILTINDIR = $(LIBDIR)/ecdboost/builtins
CPPDEP = src/*.cpp $(BUILTINDIR)/*.cpp
BOOSTDIR = /home/bitcraze/projects/boost_1_57_0

all:
	g++ -I$(BOOSTDIR) -I$(LIBDIR) -fpermissive -std=c++11 $(CPPDEP) -o test.bin

