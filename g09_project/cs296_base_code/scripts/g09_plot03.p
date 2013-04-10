set datafile separator ","
set autoscale
set term png
set output "./plots/g09_plot03.png"
plot "./data/g09_data.csv" using 1:3 with lines smooth unique title "step time averaged over all iteration values","./data/g09_data.csv" using 1:4 with lines smooth unique title "collision time averaged over all iteration values","./data/g09_data.csv" using 1:5 with lines smooth unique title "velocity update time averaged over all iteration values","./data/g09_data.csv" using 1:6 with lines smooth unique title "position update time averaged over all iteration values"
set title "Plot 03"
set xlabel "Reruns"
set ylabel "Time in ms"


