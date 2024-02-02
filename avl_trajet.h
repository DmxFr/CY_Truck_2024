#include <stdbool.h>
#include "model.h"
#ifndef AVLTrajet_h
#define AVLTrajet_h


typedef struct _chainon {
    Ville value;
    struct _chainon* next;
} Chainon;

typedef struct _AVLTrajet {
    int value;
    Chainon* list;
    struct _AVLTrajet* left;
    struct _AVLTrajet* right;
    int balance;
} AVLTrajet;



AVLTrajet* createAVLTrajet(Ville value);

void printAVLTrajetInfix(AVLTrajet* avl);

int heightAVLTrajet(AVLTrajet* avl);

int getBalanceAVLTrajet(AVLTrajet* avl);

AVLTrajet* balanceAVLTrajet(AVLTrajet* avl);

AVLTrajet* insertAVLTrajet(AVLTrajet* avl, Ville value);

AVLTrajet* rotateLeftTrajet(AVLTrajet* avl);

AVLTrajet* rotateRightTrajet(AVLTrajet* avl);

AVLTrajet* rotateDoubleLeftTrajet(AVLTrajet* avl);

AVLTrajet* rotateDoubleRightTrajet(AVLTrajet* avl);

#endif