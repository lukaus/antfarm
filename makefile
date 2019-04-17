MAIN 		= antfarm.cpp
CLASSES		= src/simulation.cpp src/node.cpp src/nodelist.cpp src/entity.cpp
COMPFLAGS	= -std=c++17 -o
LINKFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system
COMPILER 	= g++
EXEC		= antfarm 
DEBUG_EXEC	= dbg-antfarm 

all: main

main : $(PROGRAMS)
	$(COMPILER) $(COMPFLAGS) $(EXEC) $(MAIN) $(CLASSES) $(LINKFLAGS)

pure : 
	rm $(EXEC)

debug: $(PROGRAMS)
	$(COMPILER) -g $(COMPFLAGS) $(DEBUG_EXEC) $(MAIN) $(CLASSES) $(LINKFLAGS)
