# Based on Peter Miller's "Recursive Make Considered Harmful", 1997, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25
MODULES:= src  #name the subfolders to compile
TESTING:= test
CXXTEST:= cxxtest
CPPFLAGS += $(patsubst %,-I%,$(MODULES))
CPPFLAGS += $(patsubst %,-I%,$(TESTING))
# C Compiler not passed to ./depend.sh
CC=g++
CPPFLAGS += --std=c++11


# Generate the source & required libraries in each $(module)/module.mk file through the include
# There must be only one main
MAIN :=
LIBS :=
SRC := 
include $(patsubst %,%/module.mk,$(MODULES))
OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC)))
MAINOBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(MAIN)))

# Generate the source for testing
TESTSRC :=
include $(patsubst %,%/module.mk,$(TESTING))
TESTOBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(TESTSRC)))

CXXTSRC :=
include $(patsubst %,%/module.mk,$(CXXTEST))
CXXTOBJ := $(patsubst %.h,%.o,$(filter %.h,$(CXXTSRC)))


.PHONY: clean sortaclean all tests
all: TissueCells $(TESTOBJ:.o=.t) cxxtests

sortaclean:
	rm $(OBJ) $(OBJ:.o=.d) $(TESTOBJ) $(TESTOBJ:.o=.d)

clean:
	rm $(OBJ) $(OBJ:.o=.d) $(TESTOBJ) $(TESTOBJ:.o=.d) TissueCells $(TESTOBJ:.o=)

cxxtests: $(CXXTOBJ:.o=.t)

# .o dependencies will build automatically
TissueCells: $(OBJ) $(MAINOBJ)
	$(CC) -o $@ $^ $(LIBS)

# .o dependencies will build automatically
$(TESTING)/%.t: $(TESTING)/%.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

# .o dependencies build according to cxxtest rules.
# Targets that match this rule will be only those specified in module.mk.
$(CXXTEST)/%.t: $(CXXTEST)/%.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(CXXTEST)/%.o: $(CXXTEST)/%.h
	cxxtestgen --error-printer -o $*.cpp $<
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $*.cpp

include $(OBJ:.o=.d)

# Does not pass $(CC) to ./depend.sh 
%.d: %.cpp
	./depend.sh `dirname $<` $(CFLAGS) $< > $@
