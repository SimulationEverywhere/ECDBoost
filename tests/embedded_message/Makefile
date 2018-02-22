LIBDIR = ../../..

BUILTINDIR = $(LIBDIR)/ecdboost/builtins

CPPDEP = src/*.cpp $(BUILTINDIR)/*.cpp

all:
	g++  -I$(LIBDIR) -fpermissive -std=c++11 $(CPPDEP) -o test.bin

