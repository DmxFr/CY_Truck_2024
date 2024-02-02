/*#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "avl_trajet.h"*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "util.h"
#include "model.h"
#include "avl.h"
#include "avl_ville.h"
#include "avl_trajet.h"
#include "io.h"

#include "util.c"
#include "model.c"
#include "avl.c"
#include "avl_ville.c"
#include "avl_trajet.c"
#include "io.c"
#include "ts.c"



int main(int argc, char* argv[]) {
    clock_t end, start = clock();
    double time;
    printf("\n\n");


    if(argc != 3){
        printf("nombre d'argument incorrecte : ./main <fichier> <traitement>");
    }

    FILE* fichier = ouvrirFichier(argv[1], "r");

    if(strcmp("-t", argv[2]) == 0){

       Ville ville;
        strcpy(ville.nom_ville, "zzzz"); // z pour qu'il soit à la fin
        ville.trajets_total = 0;
        ville.trajet_depart = 0;

        AVLNom* avl_nom = createAVLVille(ville);
        AVL* avl_temp;
        liretoutelesEtape(fichier, avl_nom, avl_temp, 0); // lire depuis le fichier et mettre dans l'avl pour les trier ; option -t -> arg 3 = 0
        fclose(fichier);

        //printAVLInfixRecVille(avl_nom);
        //printf("\n\n\n");



        AVLTrajet* avl_trajet = createAVLTrajet(ville);// créer un avl qui trie en fonction des trajets


        parcoursAVLVille(avl_nom, avl_trajet); // ajoute les villes de avl_nom à l'avl_trajet en triant par trajet
        //printf("\n");
        //printAVLInfixRecTrajet(avl_trajet);
        //printf("\n\n");
        Ville tableau[10];
        int nbr = 0;
        recup_AVLtrajet(avl_trajet, tableau, &nbr);// lire les 10 premières valeurs de avl_trajet et les mettre dans le tableau

        avl_nom = createAVLVille(ville); // mettre les ville dans le tableau qui trie par nom
        for(int i=0; i<10; i++){
            insertAVLVille(avl_nom, tableau[i], 1, 1);
        }

        //printf("\n\n\n");
        //printAVLInfixRecVille(avl_nom);
        //printf("\n\n\n");
        nbr = 0; // compteur
        recup_AVLnom(avl_nom, tableau, &nbr);// lire les 10 premières valeurs de avl_nom et les mettre dans le tableau


        fichier = ouvrirFichier("demo/temp.csv", "w"); 

        for(int i=0; i<10; i++){
            fprintf(fichier, "%s;%d;%d", tableau[i].nom_ville, tableau[i].trajets_total, tableau[i].trajet_depart);// écrre nom;trajet_total;trajet_depart dans le fichier de sortie
            if(i<9){
                fprintf(fichier, "\n"); // pour eviter d avoir une 11e ligne vide
            }
        }

        fclose(fichier);

    }else if(strcmp("-l", argv[2]) == 0){

        AVL* avl1 = NULL;
        AVL* avl2 = createAVL(0, 0);
        AVL* avl3 = createAVL(0, 0);
        AVLNom* avl_temp = NULL;
        avl1 = liretoutelesEtape(fichier, avl_temp, avl1, 1); // lire depuis le fichier et mettre dans l'avl pour les trier ; option -t -> arg 3 = 1
        fclose(fichier);
        parcoursAVL(avl1, avl2); // faire un second avl, et le remplir en inversant l'ordre des arguments -> était trié par id en retenant la distance -> sera trié par distance en retenant les id
        printAVLInfixRec2(avl2);
        int tab[20];
        int nbr = 0; // compteur
        recup_AVL(avl2, tab, &nbr); // récupérer les 10 premières valeurs
        parcoursAVL(avl2, avl3); // faire un troisieme avl, et le remplir en inversant l'ordre des arguments -> était trié par distance -> sera trié par id (car demandé trié par id croissant)
        nbr = 0;
        int tab2[20];
        recup_AVL(avl3, tab2, &nbr); // récupérer les 10 premières valeurs
        
        fichier = ouvrirFichier("demo/temp.csv", "w"); 

        for(int i=0; i<19; i+=2){ //20-1 car contient un i+1
            fprintf(fichier, "%d;", tab2[i]);// écrire l'id
            fprintf(fichier, "%d\n", tab2[i+1]);// écrire la distance
            if(i+1<19){
                fprintf(fichier, "\n"); // pour eviter d avoir une 11e ligne vide
            }
        }

        fclose(fichier);

    }else if(strcmp("-s", argv[2]) == 0){

        int id_trajet;
        double distance;
        int compteur;
        EtapeAVL *arbre = NULL;
        Trajet *pliste = NULL; // Initialisez votre liste à NULL
        Trajet *tmp = pliste;
        // Boucle while qui continue tant que le fichier ne renvoie pas une erreur du type EOF 
        while (feof(fichier) != true){ 
            compteur++;
        // Récupération de l'ID_trajet et de la distance associée de l'étape et insertion dans la liste chainée
            fscanf(fichier, "%d", &id_trajet);
            fscanf(fichier, "%lf", &distance);
            EtapeAVL *nouvelle_etape = newEtapeAVL(id_trajet, distance);
            pliste = insertPliste(pliste, nouvelle_etape);
        }
        // Insertion des chainons de la liste chainée dans l'AVL, chainons triés dans l'AVL par "distance_max-distance_min"
        arbre = insertAVLFromList(pliste, arbre);
        pliste=NULL;
        // Récupération des 50 plus grandes "distance_max-distance_min" et écriture dans le fichier de sortie
        fichier = ouvrirFichier("demo/temp.csv", "w");
        processStats(arbre, fichier);
        fclose(fichier);
        // Libération de l'espace mémoire alloué de la liste chainée
        while (pliste != NULL) {
        Trajet *temp = pliste;
        pliste = pliste->next;
        free(temp);
        }

    }else{
        printf("Erreur, l'argument %s n'est pas reconnu\n", argv[2]);
        exit(1);
    }

    end = clock();
    time = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("\ntemps d'éxécution de main.c : %.2fs\n", time);
    return 0;
}