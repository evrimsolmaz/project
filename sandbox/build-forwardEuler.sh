gcc -o simpleODE-forwardEuler simpleODE-forwardEuler.c -lm

gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c simpleODE-forwardEuler-GSL.c
gcc -o simpleODE-forwardEuler-GSL -L$TACC_GSL_LIB simpleODE-forwardEuler-GSL.o -lgsl -lgslcblas -lm

