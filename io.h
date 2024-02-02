/*
#include <stdio.h>
#include "avl_trajet.h"
#include "model.h"
#ifndef IO_H
#define IO_H*/

Etape lireLigneEtape(FILE *fichier); 

AVL* liretoutelesEtape(FILE *fichier, AVLNom *avl, AVL* avl2, int option);

void recup_AVLtrajet(AVLTrajet* avl, Ville tableau[10], int* nbr);

void recup_AVLnom(AVLNom* avl, Ville tableau[10], int* nbr);

void recup_AVL(AVL* avl, int tableau[10], int* nbr);



//#endif