gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -c chargedParticleMotion.c
gcc -o chargedParticleMotion -L$TACC_GSL_LIB chargedParticleMotion.o -lgsl -lgslcblas -lm

