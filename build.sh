gcc -o simpleODE simpleODE.c -lm

gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c simpleODE-GSL.c
gcc -o simpleODE-GSL -L$TACC_GSL_LIB simpleODE-GSL.o -lgsl -lgslcblas -lm

