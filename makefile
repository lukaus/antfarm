

CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -g -std=c++17
CPPFLAGS = -DSFML
LDFLAGS = -static-libstdc++
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics

# source directory
SRC := src

# where to find additional c++ source and header files
# make sure to use the $(SLASH) variable for the directory seperator if
# a subdirectory is included
# example: dir$(SLASH)nextdir
cppdirs =

# a list of headers to pre-compile
pchfiles =

# output directory
BUILD := build

# name of output program
program = antfarm


# autodetect os
OSTARGET ?= UNKNOWN

ifeq ($(OSTARGET),UNKNOWN)
	ifeq ($(OS),Windows_NT)
		OSTARGET := WINDOWS
	else
		UNAME := $(shell uname -s)
		ifeq ($(UNAME),Linux)
			OSTARGET := LINUX
		endif
		ifeq ($(UNAME),Darwin)
			OSTARGET := MACOSX
		endif
	endif
endif

ifeq ($(OSTARGET),LINUX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	SLASH = /
	CP := cp
	PREFIX ?= /usr/local

	# compiler/linker programs
	CC := gcc
	CXX := g++
	CPP := g++
	LD := g++

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),MACOSX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	CP := cp
	SLASH = /
	PREFIX ?= /usr/local

	# compiler/linker programs
	CC := gcc
	CXX := g++
	CPP := g++
	LD := g++

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),WINDOWS)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -Iinclude $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -Llib
	LDLIBS += -lmingw32
	RM := del /F/Q
	RMDIR := rmdir /S/Q
	MKDIR := mkdir
	CP := robocopy
	SLASH = \\
	PREFIX ?=

	# compiler/linker programs
	CC := gcc
	CXX := g++
	CPP := g++
	LD := g++

	# extension of output program
	program := $(addsuffix .exe,$(program))
endif

INCDIRS = $(SRC) $(addprefix $(SRC)/,$(cppdirs))
VPATH = $(INCDIRS)
cppsrc = $(wildcard $(SRC)/*.cpp $(addsuffix /*.cpp,$(INCDIRS)))
objects = $(patsubst $(SRC)/%.o,$(BUILD)/%.o,$(cppsrc:.cpp=.o))
depends = $(objects:.o=.d)
gchfiles = $(addsuffix .gch, $(pchfiles))
DESTDIR =

all: $(BUILD)/$(program)
	@echo build complete!

# build single file
single: $(BUILD)/$(in).o

$(BUILD)/$(program): $(objects)
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@echo linking "$^" into "$@" using these libraries: "$(LDLIBS)"

$(objects): $(gchfiles)

$(BUILD)/%.o: %.cpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	@echo compiling "$<" to "$@" with $(CXX)

%.hpp.gch: %.hpp
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $<
	@echo precompiling header "$<" to "$@" with $(CXX)

$(objects) $(depends): | $(BUILD)

$(BUILD):
	@$(MKDIR) $(BUILD) $(addprefix $(BUILD)$(SLASH),$(cppdirs))
	@echo creating directories

# rule to generate a dependency file
$(BUILD)/%.d: %.cpp
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@
	@echo generating dependencies for "$<"

# include all dependency files in the makefile
-include $(depends)

.PHONY: clean install uninstall
clean:
#	$(RM) $(subst /,$(SLASH),$(objects)) $(subst /,$(SLASH),$(depends)) $(subst /,$(SLASH),$(BUILD)/$(program))
	@echo cleaning...
	@$(RMDIR) $(BUILD)
	@$(RM) $(SRC)$(SLASH)*.gch
	@echo done.

install: $(BUILD)/$(program)
ifeq ($(OSTARGET),WINDOWS)
	-$(CP) /S $(BUILD) $(DESTDIR)$(PREFIX)bin $(program)
	-$(CP) /S data $(DESTDIR)$(PREFIX)bin$(SLASH)data
	-$(CP) ./ $(DESTDIR)$(PREFIX)bin *.dll
else
	$(MKDIR) $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) $< $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) -r ./data $(DESTDIR)$(PREFIX)/bin/$(program)
endif

uninstall:
ifeq ($(OSTARGET), WINDOWS) 
	$(RMDIR) $(DESTDIR)$(PREFIX)bin
else 
	$(RMDIR) $(DESTDIR)$(PREFIX)$(SLASH)bin$(SLASH)$(program)
endif

help:
	@echo Commands:
	@echo make all ---------------------------------- builds the program and puts all the output files in a directory called build
	@echo make single in="<path-to-file/file>" ------ builds only a single file (omit the .cpp or .c extension and ignore the quotes as well)
	@echo make install ------------------------------ builds the program just like make all and installs the final files to a directory
	@echo make uninstall ---------------------------- will remove all the files from the install directory
	@echo make clean -------------------------------- will remove the build directory
