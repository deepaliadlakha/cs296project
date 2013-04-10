set datafile separator ","
set autoscale
set term png
set output "./plots/g09_plot02.png"
plot "./data/g09_data.csv" using 2:3 with lines smooth unique title "step time averaged over all reruns","./data/g09_data.csv" using 2:4 with lines smooth unique title "collision time averaged over all reruns","./data/g09_data.csv" using 2:5 with lines smooth unique title "velocity update time averaged over all reruns","./data/g09_data.csv" using 2:6 with lines smooth unique title "position update time averaged over all reruns"
set title "Plot 02"
set xlabel "Iteration Values"
set ylabel "Time in ms"


