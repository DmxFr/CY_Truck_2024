set term png
set output 'images/graphique_d1.png'
set style fill solid
set boxwidth 0.5
set xlabel 'Nombre de trajets'
set ylabel 'Conducteurs'
set title 'Top 10 conducteurs avec le plus de trajets'
set ytics rotate by -45
plot 'demo/data.txt' using 2:xtic(1) with boxes notitle
