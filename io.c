/*#include <stdio.h>
#include "avl_trajet.h"
#include "model.h"*/


Etape lireLigneEtape(FILE *fichier){
    Etape etape;
    fscanf(fichier, "%d;%d;%49[^;];%49[^;];%f;%49[^\n]", &etape.route_id, &etape.step_id, etape.town_a, etape.town_b, &etape.distance, etape.driver_name);
    return etape;
}






AVL* liretoutelesEtape(FILE *fichier, AVLNom *avl, AVL* avl2, int option){ // option = 0 -> -t // option = 1 -> -l

   while(getc(fichier) != '\n'){} // sauter la premiere ligne (à cause des noms des colonnes)

    while(!feof(fichier)){ // feof renvoie une valeur non nulle si on est à la fin du fichier
        
        int i=0;
        while(!feof(fichier)){ // tester si le fichier se termine par une ligne vide
            fgetc(fichier);
            i++;
            if(i>2){
                break;
            }
        }
        if(feof(fichier)){
            break;
        }
        fseek(fichier, -3, SEEK_CUR);

        Etape etape = lireLigneEtape(fichier);

        if(option == 0){ // option -t
            Ville ville_depart;
            Ville ville_arrivee;
    
            strcpy(ville_depart.nom_ville, etape.town_a); // ville de départ
            ville_depart.trajets_total=1;
            ville_depart.trajet_depart=1;
    
            strcpy(ville_arrivee.nom_ville, etape.town_b); // ville d'arrivee
            ville_arrivee.trajets_total=1;
            ville_arrivee.trajet_depart=0;
    
            
            if(strlen(ville_depart.nom_ville) != 0 && strlen(ville_arrivee.nom_ville) != 0){
                insertAVLVille(avl, ville_depart, (float)etape.route_id, (float)etape.step_id);
                insertAVLVille(avl, ville_arrivee, (float)etape.route_id, (float)etape.step_id);
                //printf("%s -- %s", ville_depart.nom_ville, ville_arrivee.nom_ville);
            }
        }else if(option == 1){ // option -l
            int a=0;
            avl2 = insertAVL(avl2, (float)etape.route_id, etape.distance, &a ,1); // trie par id
            //printf("%d -- %f\n", etape.route_id, etape.distance);
            //printAVLInfixRec2(avl2);
            //printf("\n");
        }

        
    }
    return avl2;
    
}




void recup_AVLtrajet(AVLTrajet* avl, Ville tableau[10], int* nbr){
    if(*nbr < 10 && avl != NULL){
        recup_AVLtrajet(avl->right, tableau, nbr); // parcourir l'avl
        //printf("%d ", avl->list->value.trajets_total);
        Chainon* chainon = avl->list;
        while(*nbr<10 && chainon != NULL){ // quand on a trouvé le noeud avec les villes qui apparaissent le + de fois, on les met dans le tableau et on continue
            tableau[*nbr] = chainon->value;
            //printf("%s %d (i=%d) -- ", chainon->value.nom_ville, chainon->value.trajets_total, *nbr);
            *nbr+=1;
            chainon = chainon->next;
        }
        recup_AVLtrajet(avl->left, tableau, nbr);
    }
}

void recup_AVLnom(AVLNom* avl, Ville tableau[10], int* nbr){
    if(*nbr < 10 && avl != NULL){
        recup_AVLnom(avl->left, tableau, nbr);
        if(*nbr >= 10){
            return;
        }
        tableau[*nbr] = avl->value;
        *nbr+=1;
        recup_AVLnom(avl->right, tableau, nbr);
    }
}


void recup_AVL(AVL* avl, int tableau[20], int* nbr){
    if(*nbr < 20 && avl != NULL){
        recup_AVL(avl->left, tableau, nbr);
        if(*nbr >= 20){
            printf("erreur recup_AVL()");
            return;
        }
        tableau[*nbr] = avl->value;
        tableau[(*nbr)+1] = avl->value;
        *nbr+=2;
        recup_AVL(avl->right, tableau, nbr);
    }
}




