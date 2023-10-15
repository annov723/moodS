set terminal dumb 80 35 aspect 1 ansi
set boxwidth 0.5
set style fill solid
set title "moodS amount chart"
set xlabel "moods"
set ylabel "amount"
set xrange [0:4]
plot "moods_chart.dat" using 1:3:xtic(2) with boxes