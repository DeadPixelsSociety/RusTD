CC=g++
SFML_PATH=C:\Users\Julien\Library\SFML-2.3.2
TARGET=DC
CFLAGS=-std=c++11 -W -Wall -O2 -DNDEBUG -Doff64_t=_off64_t -DDATA_COMPILER -I$(SFML_PATH)/include
LFLAGS=-L$(SFML_PATH)/lib 
LOPTS=-lsfml-graphics -lsfml-window -lsfml-system
CFILES=src/lib/Animation.cpp src/lib/TCreep.cpp src/lib/TDoodad.cpp src/lib/tinyxml2.cpp src/lib/TTower.cpp src/lib/DataCompiler.cpp
OFILES=$(addprefix obj/DC/Release/,$(notdir $(CFILES:.cpp=.o)))
all: $(OFILES)
	$(CC) $(LFLAGS) -o bin/$(TARGET) $^ $(LOPTS)
obj/DC/Release/%.o: src/lib/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<