module load TACC/1.0 gcc/5.2.0 cray_mpich/7.3.0 gsl/2.2.1 gnuplot/5.0.1 boost/1.59

gcc -o simpleODE simpleODE.c -lm

gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c simpleODE-GSL.c
gcc -o simpleODE-GSL -L$TACC_GSL_LIB simpleODE-GSL.o -lgsl -lgslcblas -lm

rm simpleODE-GSL.o
