set logscale x
set logscale y
set format y "10^{%L}"
set ticslevel 0
set nokey
set grid
set term eps
set xlabel "Step size (h)"
set ylabel "Error norm"
set output 'SimpleODEConvergence.eps'

set multiplot layout 1,2 title "Error convergence of y'(x)=y(x) with the IC y(0)=1\n RK4 order of convergence=4"
set title "My RK4"
plot "convergenceDataSimpleODEmyRK4.dat" u 1:2 with lines
set title "GSL-RK4"
plot "convergenceDataSimpleODEGSLRK4.dat" u 1:2 with lines
unset multiplot

set multiplot layout 1,2
set title "GSL-RK23, order of convergence=3"
plot "convergenceDataSimpleODEGSLRK23.dat" u 1:2 with lines
set title "GSL-RK89"
plot "convergenceDataSimpleODEGSLRK89.dat" u 1:2 with lines
unset multiplot
