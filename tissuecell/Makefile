CC=g++
CFLAG=--std=c++11
DP=-D DP
#IPATH=
#LPATH=
CPP=tissuecell.cpp
H=tissuecell.h

all: single_precision double_precision

single_precision: $(CPP) $(H)
	$(CC) $(CFLAG) $(H) $(CPP) -o TissueCells_sp

double_precision: $(CPP) $(H)
	$(CC) $(CFLAG) $(DP) $(H) $(CPP) -o TissueCells_dp
