# Files
EXEC := chargedParticleMotion
SRC := funcsandjacs.c probsandmethods.c chargedParticleMotion.c
OBJ := $(patsubst %.c,%.o,$(SRC))
# Options
CC := gcc
CFLAGS := -Wall
#LDFLAGS := 
LDLIBS := -lgsl -lgslcblas -lm -lgrvy
INC := $(TACC_GSL_INC)
#GSL_INC:= $(TACC_GSL_INC/gsl)
GRVY_INC:= $$HOME/bin/grvy/include
LIB := $(TACC_GSL_LIB)
GRVY_LIB:= $$HOME/bin/grvy/lib -Wl,-rpath,$$HOME/bin/grvy/lib
# Rules
all: $(EXEC) simpleODEmyRK4
simpleODEmyRK4: simpleODEmyRK4.c
	$(CC) -o $@ $^ -lm
$(EXEC): $(OBJ)
	$(CC) -L$(LIB) -L$(GRVY_LIB) $(LDLIBS) -o $@ $^
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -I$(INC) -I$(INC)/gsl -I$(GRVY_INC) -c $^
chargedParticleMotion.o probsandmethods.o: funcsandjacs.h probsandmethods.h
funcsandjacs.o: funcsandjacs.h
# Useful phony targets
.PHONY: clean clobber neat moreneat echo
clean: clobber
	$(RM) $(EXEC)
clobber: neat
	$(RM) $(OBJ)
neat: moreneat 
	$(RM) *~ .*~
moreneat:
	$(RM) output.dat *.eps *.gch simpleODEmyRK4
echo: 
	@echo $(OBJ)

