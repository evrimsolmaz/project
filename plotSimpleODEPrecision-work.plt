set logscale x
set logscale y
set format y "10^{%L}"
set format x "10^{%L}"
set ticslevel 0
set key default
set grid
set term eps
set ylabel "Overall wall clock time (seconds)"
set xlabel "Error norm"
set output 'SimpleODEPrecision-work.eps'

set title "Precision-work diagram"
plot "convergenceDataSimpleODEmyRK4.dat" u 2:3 with lines title 'my RK4' ,\
     "convergenceDataSimpleODEGSLRK4.dat" u 2:3 with lines title 'GSL-RK4'
