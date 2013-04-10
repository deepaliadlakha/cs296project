set datafile separator ","
set autoscale
set term png
set output "./plots/g09_plot01.png"
plot "./data/g09_data.csv" using 2:3 with lines smooth unique title "step time averaged over all reruns", "./data/g09_data.csv" using 2:7 with lines smooth unique title "loop time averaged over all reruns"
set title "Plot 01"
set xlabel "Iteration Values"
set ylabel "Time in ms"


