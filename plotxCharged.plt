set ticslevel 0
set key below
set term eps
set xlabel "x"
set ylabel "y"
set zlabel "z"

reset
unset border
unset xtics
unset ytics

set output 'chargedParticleMotion.eps'

file_exists(file) = system("[ -f '".file."' ] && echo '1' || echo '0'") + 0

if ( file_exists("outputAnalytical.dat") ) {
set multiplot layout 1, 2
set title "Numerical solution of the trajectory"
splot "output.dat" u 2:3:4 with lines
set title "Analytical solution of the trajectory"
splot "outputAnalytical.dat" u 2:3:4 with lines
unset multiplot
} else {
set title "Numerical solution of the trajectory"
splot "output.dat" u 2:3:4 with lines
}
