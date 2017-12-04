gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c vanderPol-GSL.c
gcc -o vanderPol-GSL -L$TACC_GSL_LIB vanderPol-GSL.o -lgsl -lgslcblas -lm

