gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c example.c
gcc -o example -L$TACC_GSL_LIB example.o -lgsl -lgslcblas -lm
     
