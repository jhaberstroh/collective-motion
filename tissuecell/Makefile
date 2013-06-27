# Inspiration from Peter Miller's "Recursive Make Considered Harmful", 1997, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25
MODULES:= src  #name the subfolders to compile
TESTING:= test
CPPFLAGS += $(patsubst %,-I%,$(MODULES))
CPPFLAGS += $(patsubst %,-I%,$(TESTING))
# C Compiler not passed to ./depend.sh
CC=g++
CPPFLAGS += --std=c++11


# Generate the source & required libraries in each $(module)/module.mk file through the include
LIBS :=
SRC := 
include $(patsubst %,%/module.mk,$(MODULES))
OBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(SRC)))
#DPOBJ := $(patsubst %.cpp,%_dp.o,$(filter %.cpp,$(SRC)))

# Generate the source for testing
TESTSRC :=
include $(patsubst %,%/module.mk,$(TESTING))
TESTOBJ := $(patsubst %.cpp,%.o,$(filter %.cpp,$(TESTSRC)))


DPFLAG=-D DP



.PHONY: clean all
all: TissueCells_sp $(TESTOBJ:.o=)

clean:
	rm $(OBJ) $(OBJ:.o=.d) $(TESTOBJ) $(TESTOBJ:.o=.d)

# .o dependencies will build automatically
TissueCells_sp: $(OBJ)
	@echo "TESTING FILES: " $(TESTSRC:.o=)
	$(CC) -o $@ $(OBJ) $(LIBS)

# .o dependencies will build automatically
test/%: test/%.o
	@echo "TESTING FILES: " $^
	$(CC) -o $@ $^ $(LIBS)



include $(OBJ:.o=.d)

# Does not pass $(CC) to ./depend.sh 
%.d: %.cpp
	./depend.sh `dirname $<` $(CFLAGS) $< > $@


#TissueCells_dp: $(DPOBJ)
#	$(CC) -o $@ $(DPOBJ) $(LIBS)

# Matches for double precision builds
#%_dp.o: %.cpp
#	$(CC) $(DP) $^ -o $@

# Matches for single precision builds and test builds
#%.o: %.cpp
#	$(CC) $^ -o $@
