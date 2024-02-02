
# Projet CY-Truck




## Description

- Ce projet vise à créer un outil de gestion logistique pour une société nationale de transport routier.

 - Ce projet consiste à gérer des données logistiques volumineuses et variées à l'aide de traitements en shell ou en C. 
 
 - Ce programme doit pouvoir analyser un fichier de données de type CSV et générer des graphiques pour résumer les activités de l'entreprise.


- Ce fichier CSV contient les éléments : "RouteID","StepID","Town A","Town B", "Distance", "Driver Name". Respectivement  l’identifiant unique du trajet routier, l’identifiant de l’étape pour ce trajet spécifiquement, les noms des villes de départ et d’arrivée pour cette étape, la distance parcourue en km, et enfin le nom complet du conducteur sur ce trajet.

- Le script shell utilise GnuPlot qui permet de générer des graphiques.

- Ensuite les programmes, les graphiques sont placés dans des dossiers spécifiques afin d'obtenir une meilleure gestion.



##  Installation 

- Installation de GnuPlot sur Ubuntu afin de générer des graphiques à partir de données:
 
sudo apt-get install gnuplot

- Make pour construire automatiquement des programmes et des bibliothèques exécutables:

sudo apt-get install make


## GITHUB

https://github.com/DmxFr/CY_Truck_2024


## Exécuter le Script

-avoir l'autorisation d'executer : chmod +x main.sh

-pour exécuter le programme : ./main.sh [fichier.csv] [option]


## Options

Les différentes options correspondent aux diverses opérations pouvant etre effectuées avec le script. Il y a :

-d1 : cette option  devra créer un graphique de type histogramme
horizontal avec en ordonnée les noms complets des conducteurs, et en abscisse le nombre de trajets effectués. Le conducteur avec le plus de trajet sera placé en haut du graphique. Elle représente les 10 conducteurs avec le plus de trajets.

-d2 : cette option  devra créer un graphique de type histogramme
horizontal avec en ordonnée les noms complets des conducteurs et en abscisse la distance totale parcourue. Le conducteur avec le plus de distance sera placé en haut du graphique. Elle représente les 10 conducteurs qui ont parcouru les plus longues distances.

-l : cette option devra créer un graphique de type histogramme
vertical avec en abscisse l’identifiant du trajet, et en ordonnée la distance en km. Elle représente les 10 trajets les plus longs en fonction de la distance totale. 

-t : cette option devra créer un graphique de type histogramme
regroupé. On retrouvera en abscisse les noms des villes, par ordre alphabétique, et en ordonnée le nombre de trajets.
Pour chaque ville, il y aura 2 barres verticales, celle de gauche indiquera le nombre de trajets total qui traversent cette ville, et celle de droite le nombre de fois où cette ville est la ville de départ d’un trajet. Elle représente les 10 villes les plus traversées par ordre alphabétique.

-s : cette option devra créer un graphique de type courbes min-max-moyenne, c’est à dire 2 courbes indiquant pour chaque abscisse les valeurs min et max des distances, et une troisième entre les deux pour indiquer la moyenne. En abscisse il y aura les identifiants des trajets, et en ordonnée les distances en km (mini, moyenne, maxi). Elle consiste à recueillir des statistiques sur les étapes telle que distance min, max et moyennes.






## Auteurs

HODGE Rodrigue

FERNANDES Damien
