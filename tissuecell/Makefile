# Based on Peter Miller's "Recursive Make Considered Harmful", 1997, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25
# >> NOTE: All c++ & CxxTest files must have .cpp & .h suffix!,
PWD:=$(abspath $(dir $(lastword $(MAKEFILE_LIST))))

CPPFLAGS:=-I/home/jhaberstroh/Downloads/sourcebuilds/Qt/5.1.0/gcc_64/include -I/home/jhaberstroh/Downloads/sourcebuilds/icu/include
LIBDIR := $(patsubst -I%/include, -L%/lib, $(CPPFLAGS))

MODULES:= src
GUIMODULE := qtgui #name the subfolders to compile
CXXTEST:= cxxtest
CPPFLAGS += $(patsubst %,-I%,$(MODULES))
CPPFLAGS += $(patsubst %,-I%,$(TESTING))


# Generate the source & required libraries in each $(module)/module.mk file through the include
# There must be only one main
MAIN :=
SRC := 
HEADERS :=
LIBS :=
#######################
include $(patsubst %,%/module.mk,$(MODULES))
include $(patsubst %,%/module.mk,$(GUIMODULE))
#######################
OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC)))
MAINOBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(MAIN)))
LIBS := $(patsubst %, -l%, $(LIBS))

CXXTSRC :=
include $(patsubst %,%/module.mk,$(CXXTEST))
CXXTOBJ := $(patsubst %.h,%.o,$(filter %.h,$(CXXTSRC)))


# C Compiler not passed to ./depend.sh
CC=g++
CPPFLAGS += --std=c++11 -g -fPIE -Wall


.PHONY: all sortaclean clean cxxtests GUI

all: TissueCells $(TESTOBJ:.o=.t) cxxtests GUI

sortaclean:
	rm $(CXXTOBJ:.o=.cpp) $(MAINOBJ) $(OBJ) $(OBJ:.o=.d)

clean:
	rm $(CXXTOBJ:.o=.cpp) $(CXXTOBJ:.o=.t) $(MAINOBJ) $(OBJ) $(OBJ:.o=.d) TissueCells $(patsubst %,%/module.pri,$(MODULES))

cxxtests: $(CXXTOBJ:.o=.t)

# Must come last in the all command.
# Builds the GUI using qmake, because linking to QT libraries is painful.
# module.pri files can be added by .pro files to allow the modules to be included correctly in qmake.
GUI: $(patsubst %, %/module.pri, $(MODULES))
	cd $(GUIMODULE); \
	cd simtemplate; \
	qmake; \
	make
	

# .o dependencies will build automatically
TissueCells: $(OBJ) $(MAINOBJ)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# .t files are my convention for executables from CxxTest
# Calls to this rule come from files supplied to CXXTSRC
$(CXXTEST)/%.t: $(CXXTEST)/%.o $(OBJ)
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

$(CXXTEST)/%.o: $(CXXTEST)/%.h
	cd $(CXXTEST); \
	cxxtestgen --error-printer -o $*.cpp $*.h;
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $(CXXTEST)/$*.cpp;

include $(OBJ:.o=.d)

# Does not pass $(CC) to ./depend.sh 
%.d: %.cpp
	./depend.sh `dirname $<` $(CFLAGS) $< > $@
