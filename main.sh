#!/bin/bash

for i in "$@" ;do
    # Vérifier si l'argument -h est présent
    if [ "$i" == "-h" ]; then
        echo "un fichier help à été crée. Veuiller donc regarder dans ce fichier pour voir les aides."
        exit 1
    fi
done 

# Vérifier si le fichier CSV est spécifié
if [ -z "$1" ]; then
    echo "Erreur: Veuillez spécifier le chemin du fichier CSV en tant que premier argument."
    exit 1
fi

# Vérifier et créer les dossiers temp et images et progc si nécessaire
dossiers=("progc" "images" "temp" "demo")

for dossier in "${dossiers[@]}"; do
    if [ -d "$dossier" ]; then
        rm -vf "$dossier"/*
    else
        mkdir "$dossier"
    fi
done
touch demo/trajets.csv


# Vérifier la présence de l'exécutable C
if ([ "$2" == "-t" ] || [ "$2" == "-s" ] || [ "$2" == "-l" ]) && ! [ -e "progc/main" ]; then
    echo "Compilation en cours..."
    make

    # Vérifier que la compilation s'est bien déroulée
    if [ $? -ne 0 ]; then
        echo "Erreur: La compilation a échoué."
        exit 1
    fi
fi


# Vérification du nombre d'arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <chemin_fichier_CSV> <choix_traitement>"
    exit 1
fi

# Récupération des arguments
fichier_csv="$1"
choix_traitement="$2"

# Vérification de l'existence du fichier CSV
if [ ! -f "$fichier_csv" ]; then
    echo "Le fichier CSV spécifié n'existe pas."
    exit 1
fi


function traitement_d1()
{
    #Voici un script Shell qui réalise le traitement [D1] en utilisant uniquement des commandes Unix. Assurez-vous que le fichier d'entrée est correctement formaté avec les informations des trajets. Ce script suppose que chaque ligne du fichier d'entrée représente un trajet avec le nom du conducteur.

    # Extraction et comptage des trajets par conducteur
    trajets_par_conducteur=$(cat $fichier_csv | cut -f1,6 -d";" | sort | uniq | cut -f2 -d";" | sort | uniq -c | sort -nr )

    # Récupération des 10 premiers conducteurs avec le plus grand nombre de trajets
    top_10_conducteurs=$(echo "$trajets_par_conducteur" | head -n 10)

    # Création du fichier de données pour le graphique
    echo "$top_10_conducteurs" | awk '{print $2 " " $1}' > demo/data.txt

    # Création du fichier de script pour GnuPlot
    echo "set term png" > script.gp
    echo "set output 'images/graphique_d1.png'" >> script.gp
    echo "set style fill solid" >> script.gp
    echo "set boxwidth 0.5" >> script.gp
    echo "set xlabel 'Nombre de trajets'" >> script.gp
    echo "set ylabel 'Conducteurs'" >> script.gp
    echo "set title 'Top 10 conducteurs avec le plus de trajets'" >> script.gp
    echo "set ytics rotate by -45" >> script.gp
    echo "plot 'demo/data.txt' using 2:xtic(1) with boxes notitle" >> script.gp

    # Exécution de GnuPlot avec le fichier de script
    gnuplot script.gp

    # Nettoyage des fichiers temporaires
    #rm data.txt script.gp

    echo "Le graphique a été généré avec succès."

    #Ce script utilise les commandes Unix telles que awk, sort, et uniq pour effectuer le traitement, puis génère un graphique avec GnuPlot. N'oubliez pas de rendre le script exécutable avec la commande chmod +x nom_du_script.sh et de l'appeler avec le chemin du fichier CSV en argument (./nom_du_script.sh chemin_fichier_CSV).

}


function traitement_d2()
{
    #Pour ce traitement, nous allons extraire les distances totales parcourues par chaque conducteur à partir du fichier CSV, puis nous sélectionnerons les 10 conducteurs avec les distances les plus grandes pour créer un histogramme horizontal.*/


    # Extraction et calcul des distances totales par conducteur
    distances_par_conducteur=$(awk -F';' '{total[$6]+=$5} END {for (i in total) print total[i], i}' "$fichier_csv" | sort -nr)

    # Récupération des 10 premiers conducteurs avec les distances les plus grandes
    top_10_conducteurs=$(echo "$distances_par_conducteur" | head -n 10)

    # Création du fichier de données pour le graphique
    echo "$top_10_conducteurs" | awk '{print $2 " " $1}' > demo/data_d2.txt

    # Création du fichier de script pour GnuPlot
    echo "set term png" > script_d2.gp
    echo "set output 'images/graphique_d2.png'" >> script_d2.gp
    echo "set style fill solid" >> script_d2.gp
    echo "set boxwidth 0.5" >> script_d2.gp
    echo "set xlabel 'Distance totale parcourue'" >> script_d2.gp
    echo "set ylabel 'Conducteurs'" >> script_d2.gp
    echo "set title 'Top 10 conducteurs avec la plus grande distance totale parcourue'" >> script_d2.gp
    echo "set ytics rotate by -45" >> script_d2.gp
    echo "plot 'demo/data_d2.txt' using 2:xtic(1) with boxes notitle" >> script_d2.gp

    # Exécution de GnuPlot avec le fichier de script
    gnuplot script_d2.gp

    # Nettoyage des fichiers temporaires
    rm data_d2.txt script_d2.gp

    echo "Le graphique D2 a été généré avec succès."

    # Ce script récupère les distances totales par conducteur à partir du fichier CSV, sélectionne les 10 conducteurs avec les distances les plus grandes, crée un fichier de données pour GnuPlot, génère le graphique horizontal, puis nettoie les fichiers temporaires. Assurez-vous d'adapter la colonne correspondant à la distance dans votre fichier CSV (ici, c'est la colonne 3 avec l'option -F',' '{total[$1]+=$3}).

}


function traitement_l()
{

# Entrée : fichier CSV original
input_file="$fichier_csv"

# Sortie : fichier CSV avec l'ID du trajet et la distance totale
output_file="trajets.csv"

cut -d";" -f1,5 $input_file | awk -F';' 'NR>1 {sum[$1]+=$2} END {for (id in sum) print id";"sum[id]}' | sort -t';' -k2,2nr | head -n10 > demo/"$output_file"

echo "Le fichier $output_file a été créé avec succès."



      #Calcul des distances totales par trajet
    ##distances_par_trajet=$(awk -F',' '{total[$1]+=$5} END {for (i in total) printf "%f %s\n", total[i], i}' "$fichier_csv" | sort -nr)
    # distances_par_trajet=$(awk -F ';' '{ distances[$1] += $5 } END { for (route_id in distances) printf distances[route_id], route_id }' "$fichier_csv" | sort -k1,1nr | head -n 10 | sort -k2,2nr)


    # # Récupération des 10 trajets avec les distances les plus grandes
    # top_10_trajets=$(echo "$distances_par_trajet" | head -n 10)

 # Création du fichier de données pour le graphique
    gnuplot -persist <<EOF
set terminal pngcairo enhanced font 'arial,10' size 700, 600
set output 'images/traitement_l.png'
set title 'Option -l : Distance = f(Route)'
set ylabel 'DISTANCE (Km)'
set xlabel 'ROUTE ID'
set style fill solid
# La plage maximale de yrange est ici indéfinie, elle ajustera en fonction des données
set yrange [0:]
set boxwidth 0.7

plot demo/'$output_file' using 1:xtic(2) with boxes lc rgbcolor 'spring-green' notitle
EOF

    echo "Le graphique L a été généré avec succès."


    # Ce script prend en compte un fichier CSV contenant les données des trajets routiers. Il calcule la distance totale pour chaque trajet, sélectionne les 10 trajets avec les distances les plus grandes, puis crée un graphique d'histogramme vertical montrant l'identifiant du trajet en abscisse et la distance en kilomètres en ordonnée.

}

function traitement_t()
{
    ./progc/main "$fichier_csv" -t

    gnuplot 'traitement_t.gp'
}

function traitement_s()
{
    # EN C

    # Pour un traitement aussi spécifique, une connaissance précise de la structure du fichier CSV est nécessaire. Pour simplifier, supposons que le fichier CSV a trois colonnes : ID_trajet, Ville_depart, Ville_arrivee.

    # Voici un exemple simplifié de code en C pour traiter ce cas, en utilisant des structures pour stocker les données des trajets et des villes, ainsi qu'un arbre AVL pour le tri :

    #UTILISER SSI LE CODE EN C NE FONCTIONNE PAS (VOIR SUITE)
    output_file="demo/trajets.csv"


    # Création d'un fichier temporaire pour stocker les statistiques
   head $fichier_csv -n-1 | cut -d';' -f1,5 | awk -F';' '{
    id = $1
    value = $2
    if (!min[id] || value < min[id]) min[id] = value
    if (!max[id] || value > max[id]) max[id] = value
    sum[id] += value
    count[id]++
}
END {
    for (id in min) {
        avg = sum[id] / count[id]
        printf("%d;%f;%f;%f;%f\n", id, min[id], avg,  max[id], max[id]-min[id])
    }
}' | sort -t';' -k5,5nr | cut -d';' -f1,2,3,4 | head -n50 > $output_file
    
    # Utilisation de gnuplot pour la création du graphe
    
echo -e '
		set grid nopolar
		set grid xtics mxtics ytics mytics noztics nomztics noztics nortics nomrtics nox2tics nomx2tics noy2tics nomy2tics nomcbtics
		set style data lines
		set title "Distance min moyenne et max par trajet"
		set xlabel "distance"
		set ylabel "trajet"
		Shadecolor = "#EECF83"
		set autoscale noextend
		set xtics rotated by 90 right
		set xrange [*:*]
		set terminal png size 1000,750 enhanced font "Helvetica,20"
		set output "images/graphique.png"
		plot "tmp.dat" using 1:2:3 with filledcurves fc rgb Shadecolor notitle, "tmp.dat" using 1:4 with lines set linetype 2 lc rgb "sea-green" lw 2 pt 7' | gnuplot --persist 2>/dev/null

}



# Enregistrer le temps de début
start_time=$(date +%s)


# script Shell prend en paramètre le chemin du fichier CSV d'entrée et d'autres paramètres pour choisir les traitements, vous pouvez le concevoir de la manière suivante


# Vérification et exécution des traitements en fonction des choix
case "$choix_traitement" in
    -d1)
        echo "Traitement D1 sélectionné."
        # Appel du programme C pour le traitement D1 avec le fichier CSV en argument
        #./main "$fichier_csv" conducteursAvecPlusDeTrajets
        traitement_d1
        ;;
    -d2)
        echo "Traitement D2 sélectionné."
        # Appel du programme C pour le traitement D2 avec le fichier CSV en argument
        #./main "$fichier_csv" DistanceParConducteur
        traitement_d2
        ;;
    -l)
        echo "Traitement L sélectionné."
        # Appel du programme C pour le traitement L avec le fichier CSV en argument
        #./main "$fichier_csv" TrajetsLesPlusLongs
        traitement_l
        ;;
    -t)
        echo "Traitement T sélectionné."
        # Appel du programme C pour le traitement L avec le fichier CSV en argument
        traitement_t
        ;;
    -s)
        echo "Traitement S sélectionné."
        # Appel du programme C pour le traitement L avec le fichier CSV en argument
        #./progc/main "$fichier_csv" -s
        traitement_s
        ;;
    *)
        echo "Choix de traitement non reconnu."
        exit 1
        ;;
           
esac

# Enregistrer le temps de fin
end_time=$(date +%s)

# Calculer la durée totale
duration=$((end_time - start_time))

# Afficher la durée totale
echo "Durée totale: $duration secondes"