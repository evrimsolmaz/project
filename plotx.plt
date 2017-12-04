#set xrange
#set yrange
set ticslevel 0
set key below
set term eps
set xlabel "x"
set ylabel "y"
set zlabel "z"
set output 'chargedParticleMotion.eps'
splot "output.dat" u 2:3:4 with lines

