/*#include <stdbool.h>
#include "model.h"
#ifndef AVLNom_h
#define AVLNom_h*/


typedef struct _AVLNom {
    Ville value;
    AVL* avl;
    struct _AVLNom* left;
    struct _AVLNom* right;
    int balance;
} AVLNom;



AVLNom* createAVLNomVille(Ville value);

void printAVLNomInfixVille(AVLNom* avl);

int heightAVLNomVille(AVLNom* avl);

int getBalanceAVLNomVille(AVLNom* avl);

AVLNom* balanceAVLNomVille(AVLNom* avl);

AVLNom* insertAVLNomVille(AVLNom* avl, Ville value, float id_trajet, float id_etape);

AVLNom* rotateLeftVille(AVLNom* avl);

AVLNom* rotateRightVille(AVLNom* avl);

AVLNom* rotateDoubleLeftVille(AVLNom* avl);

AVLNom* rotateDoubleRightVille(AVLNom* avl);

//#endif