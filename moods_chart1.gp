set terminal dumb 80 35 aspect 1 ansi 

set title "moodS timeline chart"
set xlabel "date"
set ylabel "mood"
set xrange [0:]
set yrange [0:4]
plot 'moods_chart.dat' with lines