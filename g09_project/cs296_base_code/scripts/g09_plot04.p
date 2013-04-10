set datafile separator ","
set autoscale
set term png
set output "./plots/g09_plot04.png"
plot "./data/g09_data.csv" using 1:3 with lines smooth unique title "step time averaged over all iteration values", "./data/g09_data.csv" using 1:7 with lines smooth unique title "loop time averaged over all iteration values"
set title "Plot 04"
set xlabel "Reruns"
set ylabel "Time in ms"


