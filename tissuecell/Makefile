# Based on Peter Miller's "Recursive Make Considered Harmful", 1997, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25
MODULES:= src  #name the subfolders to compile
CXXTEST:= cxxtest
CPPFLAGS += $(patsubst %,-I%,$(MODULES))
CPPFLAGS += $(patsubst %,-I%,$(TESTING))
# C Compiler not passed to ./depend.sh
CC=g++
CPPFLAGS += --std=c++11 -g


# Generate the source & required libraries in each $(module)/module.mk file through the include
# There must be only one main
MAIN :=
LIBS :=
SRC := 
include $(patsubst %,%/module.mk,$(MODULES))
OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC)))
MAINOBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(MAIN)))

CXXTSRC :=
include $(patsubst %,%/module.mk,$(CXXTEST))
CXXTOBJ := $(patsubst %.h,%.o,$(filter %.h,$(CXXTSRC)))

.PHONY: clean sortaclean all tests
all: TissueCells $(TESTOBJ:.o=.t) cxxtests sortaclean

sortaclean:
	rm $(CXXTOBJ:.o=.cpp) $(MAINOBJ) $(OBJ) $(OBJ:.o=.d) 
clean:
	rm $(CXXTOBJ:.o=.cpp) $(CXXTOBJ:.o=.t) $(MAINOBJ) $(OBJ) $(OBJ:.o=.d) TissueCells

cxxtests: $(CXXTOBJ:.o=.t)

# .o dependencies will build automatically
TissueCells: $(OBJ) $(MAINOBJ)
	$(CC) -o $@ $^ $(LIBS)

# .o dependencies build according to cxxtest rules.
# Targets that match this rule will be only those specified in module.mk.
$(CXXTEST)/%.t: $(CXXTEST)/%.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(CXXTEST)/%.o: $(CXXTEST)/%.h
	cd $(CXXTEST); \
	cxxtestgen --error-printer -o $*.cpp $*.h;
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $(CXXTEST)/$*.cpp;

include $(OBJ:.o=.d)

# Does not pass $(CC) to ./depend.sh 
%.d: %.cpp
	./depend.sh `dirname $<` $(CFLAGS) $< > $@
