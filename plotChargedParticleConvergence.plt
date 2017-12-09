set logscale x
set logscale y
set format y "10^{%L}"
set ticslevel 0
set nokey
set grid
set term eps
set xlabel "Step size (h)"
set ylabel "Error norm"
set output 'ChargedParticleConvergence.eps'

set multiplot layout 1,1 title "Error convergence of the charged particle motion equations\n RK4 order of convergence=4"
set title "GSL-RK4"
plot "convergenceDataChargedParticleGSLRK4.dat" u 1:2 with lines
unset multiplot

set multiplot layout 1,2
set title "GSL-RK23, order of convergence=3"
plot "convergenceDataChargedParticleGSLRK23.dat" u 1:2 with lines
set title "GSL-RK89"
plot "convergenceDataChargedParticleGSLRK89.dat" u 1:2 with lines
unset multiplot
