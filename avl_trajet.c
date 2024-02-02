/*#include <stdlib.h>
#include "avl_trajet.h"
#include "model.h"
#include "util.h"*/


Chainon* newChainon(Ville ville){
    Chainon* chainon = safeMalloc(sizeof(Chainon));
    chainon->next = NULL;
    chainon->value = ville;
    return chainon;
}


Chainon* insertChainon(Chainon* chainon, Ville ville){
    if(chainon == NULL){
        return newChainon(ville);
    }
    Chainon* chainon_temp = chainon;
    while(chainon_temp->next != NULL){
        chainon_temp = chainon_temp->next;
    }
    chainon_temp->next = newChainon(ville);
    return chainon;
}


AVLTrajet* createAVLTrajet(Ville value) {
    AVLTrajet* avl = safeMalloc(sizeof(AVLTrajet));
    avl->value = value.trajets_total;
    avl->list = newChainon(value);
    avl->left = NULL;
    avl->right = NULL;
    avl->balance = 0;
    return avl;
}

void printAVLInfixRecTrajet(AVLTrajet* avl) {
    if(avl != NULL) {
        printAVLInfixRecTrajet(avl->left);
        Chainon* chainon = avl->list;
        while(chainon != NULL){
            printf("%s %d - ", chainon->value.nom_ville, chainon->value.trajets_total);
            chainon = chainon->next;
        }
        printf("  --  ");
        printAVLInfixRecTrajet(avl->right);
    }
}

void printAVLInfixTrajet(AVLTrajet* avl) {
    printAVLInfixRecTrajet(avl);
    printf("\n");
}

int heightAVLTrajet(AVLTrajet* avl) {
    if(avl == NULL) return 0;
    else {
        int leftHeight = heightAVLTrajet(avl->left);
        int rightHeight = heightAVLTrajet(avl->right);
        return 1 + leftHeight > rightHeight ? leftHeight : rightHeight;
    }
}

AVLTrajet* balanceAVLTrajet(AVLTrajet* avl) {
    if(avl->balance >= -1 && avl->balance <= 1) return avl;
    else if(avl->balance == 2) return avl->right->balance == 1 ? rotateLeftTrajet(avl) : rotateDoubleLeftTrajet(avl);
    else return avl->left->balance == -1 ? rotateRightTrajet(avl) : rotateDoubleRightTrajet(avl);
}

AVLTrajet* insertAVLRecTrajet(AVLTrajet* avl, Ville value, int* h) {
    if(avl == NULL) { //Création d'un AVL -> équilibre +- 1
        *h = 1;
        return createAVLTrajet(value);
    } else if(value.trajets_total == avl->value) { //Noeud déjà présent
        avl->list = insertChainon(avl->list, value);
        *h = 0;
        return avl;
    } else {
        if(value.trajets_total < avl->value) { //Ajouter à gauche
            if(avl->left == NULL){
                avl->left = createAVLTrajet(value);
            }else{
                avl->left = insertAVLRecTrajet(avl->left, value, h);
            }
            *h = -*h;
        } else { //Ajouter à droite
            if(avl->right == NULL){
                avl->right = createAVLTrajet(value);
            }else{
                avl->right = insertAVLRecTrajet(avl->right, value, h);
            }
        }

        if(*h != 0) { //Si il y a eu ajout
            avl->balance += *h;
            avl = balanceAVLTrajet(avl);
            *h = avl->balance == 0 ? 0 : 1; //Valeur absolue pour éviter la double négation avec l'ajout à gauche
        }
        return avl;
    }
}

AVLTrajet* insertAVLTrajet(AVLTrajet* avl, Ville value) {
    int* h = safeMalloc(sizeof(int));
    *h = 0;
    return insertAVLRecTrajet(avl, value, h);
}

int maxTrajet(int a, int b) {
    return a > b ? a : b;
}

int minTrajet(int a, int b) {
    return a <= b ? a : b;
}

AVLTrajet* rotateLeftTrajet(AVLTrajet* avl) { //Rotate the tree to the left
    AVLTrajet* root = avl->right;
    avl->right = root->left;
    root->left = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - maxTrajet(eq_root, 0) - 1;
    root->balance = minTrajet(eq_a-2, minTrajet(eq_a+eq_root-2, eq_root-1));
    return root;
}

AVLTrajet* rotateRightTrajet(AVLTrajet* avl) { //Rotate the tree to the right
    AVLTrajet* root = avl->left;
    avl->left = root->right;
    root->right = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - minTrajet(eq_root, 0) + 1;
    root->balance = maxTrajet(eq_a+2, maxTrajet(eq_a+eq_root+2, eq_root+1));
    return root;
}

AVLTrajet* rotateDoubleLeftTrajet(AVLTrajet* avl) {
    avl->right = rotateRightTrajet(avl->right);
    return rotateLeftTrajet(avl);
}

AVLTrajet* rotateDoubleRightTrajet(AVLTrajet* avl) {
    avl->left = rotateLeftTrajet(avl->left);
    return rotateRightTrajet(avl);
}

