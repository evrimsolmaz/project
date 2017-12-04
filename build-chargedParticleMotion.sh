# module load TACC/1.0 gcc/5.2.0 cray_mpich/7.3.0 gsl/2.2.1 gnuplot/5.0.1 boost/1.59

gcc -Wall -I$TACC_GSL_INC -I$TACC_GSL_INC/gsl -I$HOME/bin/grvy/include -c chargedParticleMotion.c
gcc -o chargedParticleMotion -L$TACC_GSL_LIB -L$HOME/bin/grvy/lib -Wl,-rpath,$HOME/bin/grvy/lib chargedParticleMotion.o -lgsl -lgslcblas -lm -lgrvy

rm chargedParticleMotion.o
