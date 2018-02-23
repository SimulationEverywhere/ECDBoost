LIBDIR = ../../..

BUILTINDIR = $(LIBDIR)/ecdboost/builtins

CPPDEP = $(BUILTINDIR)/*.cpp src/*.cpp 

all:
	g++  -I$(LIBDIR) -fpermissive -std=c++11 $(CPPDEP) -o test.bin

