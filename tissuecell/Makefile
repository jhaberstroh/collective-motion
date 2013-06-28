# Based on Peter Miller's "Recursive Make Considered Harmful", 1997, AUUGN Journal of AUUG Inc., 19(1), pp. 14-25
MODULES:= src  #name the subfolders to compile
TESTING:= test
CPPFLAGS += $(patsubst %,-I%,$(MODULES))
CPPFLAGS += $(patsubst %,-I%,$(TESTING))
# C Compiler not passed to ./depend.sh
CC=g++
CPPFLAGS += --std=c++11


# Generate the source & required libraries in each $(module)/module.mk file through the include
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



.PHONY: clean sortaclean all
all: TissueCells $(TESTOBJ:.o=)

sortaclean:
	rm $(MAINOBJ) $(OBJ) $(OBJ:.o=.d) $(TESTOBJ) $(TESTOBJ:.o=.d)

clean:
	rm $(MAINOBJ) $(OBJ) $(OBJ:.o=.d) $(TESTOBJ) $(TESTOBJ:.o=.d) TissueCells $(TESTOBJ:.o=)

# .o dependencies will build automatically
TissueCells: $(OBJ) $(MAINOBJ)
	$(CC) -o $@ $(OBJ) $(MAINOBJ) $(LIBS)

# .o dependencies will build automatically
test/%: test/%.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)


include $(OBJ:.o=.d)

# Does not pass $(CC) to ./depend.sh 
%.d: %.cpp
	./depend.sh `dirname $<` $(CFLAGS) $< > $@
