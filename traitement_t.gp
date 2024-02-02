set datafile separator ";"
set terminal pngcairo enhanced font 'arial,10' size 700, 600
set output 'images/graphique_t.png'
set title 'Option -t : NB routes = t(Towns)'
set ylabel 'NB ROUTES'
set xlabel 'TOWN NAMES'
set style fill solid 
set yrange [0:]
set boxwidth 0.5
set xtics rotate by 45 right font ",8"
set bmargin 5
set style histogram clustered gap 1
set style fill solid 0.8 border

plot 'demo/temp.csv' using ($0):2:xticlabel(1) with boxes lc rgbcolor 'spring-green' notitle, \
    '' using ($0+0.2):($3) with boxes lc rgbcolor 'dark-green' notitle