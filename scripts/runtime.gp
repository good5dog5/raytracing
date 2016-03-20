reset
set auto x 
set ylabel 'time(sec)'
set yrange [0:10]
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot 'output.txt' using 2:xtic(1) with histogram title 'original', \
'' using ($0-0.06):($2+0.001):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'loop unrolling'  , \
'' using ($0+0.3):($3+0.0015):3 with labels title ' '

