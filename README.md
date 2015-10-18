# RusTD

A rusted Tower Defense game !

### Required dependencies

- SFML 2.2
- C++11

### External tools

#### Data compiler

The Data compiler program allows to compress data in a single binary file.
To use the binary loading, you just have to change ENTITIES_LOADING_MODE to LOAD_BIN in config.hpp
To compile the data compiler, you need to create a new compilation target that implements the following rules :

- Define constant DATA_COMPILER
- Compile with files :
  - Animation.hpp
  - Animation.cpp
  - config.hpp
  - TCreep.hpp
  - TCreep.cpp
  - TDoodad.hpp
  - TDoodad.cpp
  - tinyxml2.h
  - tinyxml2.cpp
  - TTower.hpp
  - TTower.cpp
- Link with the following options : 
  - sfml-graphics
  - sfml-window
  - sfml-system

You can also use the following makefile in root directory (don't forget to place tab characters for rules)
```
#Change CC, SFML_PATH and TARGET according to your system
CC=g++
SFML_PATH=C:/sfml
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
```
