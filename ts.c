



// Création structure EtapeAVL permettant le tri des données de la liste chainée pliste permettant le 1er tri des données
typedef struct EtapeAVL {
int id_trajet;
double distance;
double distance_min;
double distance_max;
double distance_max_min;
double distance_moyenne;
int hauteur;
int nombre_etapes;
struct EtapeAVL *gauche;
struct EtapeAVL *droite;
} EtapeAVL;

// Création structure Trajet permettant le tri des données par ID_Trajet
typedef struct Trajet {
 	EtapeAVL* noeud;
 	struct Trajet* next;
    struct Trajet *end;
} Trajet;


// Fonction pour calculer la hauteur d'un arbre
int height(EtapeAVL *node) {
    if (node == NULL) {
        return 0; // La hauteur d'un noeud vide est 0
    } else {
        int gauche_height = height(node->gauche);
        int droite_height = height(node->droite);

        return 1 + max(gauche_height, droite_height);
    }
}

// Fonction permettant la rotation droite de l'AVL
EtapeAVL *rotateRight2(EtapeAVL *y) {
    EtapeAVL *x = y->gauche;
    EtapeAVL *T2 = x->droite;

    // Rotation
    x->droite = y;
    y->gauche = T2;

    // Mise à jour des hauteurs
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;

    return x;
}

// Fonction permettant la rotation gauche de l'AVL
EtapeAVL *rotateLeft2(EtapeAVL *x) {
    EtapeAVL *y = x->droite;
    EtapeAVL *T2 = y->gauche;

    // Rotation
    y->gauche = x;
    x->droite = T2;

    // Mise à jour des hauteurs
    x->hauteur = max(height(x->gauche), height(x->droite)) + 1;
    y->hauteur = max(height(y->gauche), height(y->droite)) + 1;

    return y;
}

// Vérification de si l'AVL est équilibré.
int getBalance(EtapeAVL *node) {
    if (node == NULL) {
        return 0; // Le facteur d'equilibre d'un noeud vide est 0
    } else {
        return height(node->gauche) - height(node->droite);
    }
}

// Fonction permettant la création d'un nouveau noeud
EtapeAVL *newEtapeAVL(int id_trajet,double distance) {
    EtapeAVL *node = (EtapeAVL *)malloc(sizeof(EtapeAVL));
    if (node == NULL) {
        perror("Erreur d'allocation memoire");
        exit(EXIT_FAILURE);
    }
    //Insertion des données
    node->distance=distance;
    node->distance_max=distance;
    node->distance_min=distance;
    node->distance_max_min=0;
    node->nombre_etapes=1;
    node->distance_moyenne=distance/node->nombre_etapes;
    node->id_trajet = id_trajet;
    node->gauche = NULL;
    node->droite = NULL;
    node->hauteur = 1;
    return node;
}

// Fonction permettant la modification du chainon trajet en ajoutant l'étape au chainon ID_Trajet similaire
Trajet* modifierTrajet(Trajet* root, EtapeAVL* nouvelle_etape) {
    if (root == NULL || root->noeud == NULL) {
        // Gérer le cas où root ou root->noeud est NULL
        return root;
    }

    root->noeud->distance += nouvelle_etape->distance;

    // Mise à jour de distance_max du trajet si l'étape à une distance plus élevé que celle actuelle du trajet
    if (root->noeud->distance_max < nouvelle_etape->distance) {
        root->noeud->distance_max = nouvelle_etape->distance;
    }

    if (root->noeud->distance_min > nouvelle_etape->distance) {
        root->noeud->distance_min = nouvelle_etape->distance;
    }

    //  Mise à jour de distance_min du trajet si l'étape à une distance plus petite que celle actuelle du trajet
    root->noeud->distance_max_min = root->noeud->distance_max - root->noeud->distance_min;
    root->noeud->nombre_etapes += 1;
    root->noeud->distance_moyenne = root->noeud->distance / root->noeud->nombre_etapes;

    return root;
}


// Fonction permettant l'insertion de l'étape dans la liste chainée, soit création du chainon si ID_Trajet n'est pas présent sinon modification du trajet
Trajet *insertPliste(Trajet *pliste, EtapeAVL *nouvelle_etape) {
    Trajet *newNode = (Trajet *)malloc(sizeof(Trajet));
    if (newNode == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    newNode->noeud = nouvelle_etape;
    newNode->next = NULL;

    if (pliste == NULL) {
        // Si la liste est vide, le nouveau noeud devient la tête de la liste
        Trajet * inter = newNode;
        inter->end = newNode;
        return inter;
    }

    Trajet *tmp = pliste;
    // Insertion de l'étape dans le chainon trajet actuelle si même ID_Trajet
        if (tmp->end->noeud->id_trajet == nouvelle_etape->id_trajet) {
            tmp = modifierTrajet(tmp->end, nouvelle_etape);
            free(newNode); // Libérer le noeud nouvellement alloué car il n'est pas nécessaire
            return pliste; // Pas besoin d'ajouter un nouveau noeud à la liste
    }
    // Si condition If pas respectée, le pointeur ajoute l'étape en créant un chainon suivant, qui regroupera tout les ID_Trajet similaires si une des futures étapes ajoutées à le même ID_Trajet
    tmp->end->next = newNode;
    tmp->end = tmp->end->next;
    return pliste;
}

// Fonction pour insérer un nouveau noeud dans l'arbre AVL, trié par "distance_max-distance_min"
EtapeAVL *insertAVLNode(EtapeAVL *root, EtapeAVL *nouvelle_etape) {
    // Rajoute le noeud au noeud actuel si noeud actuel est vide
    if (root == NULL) {
        return nouvelle_etape;
    }
    // Compare les "distance_max-distance_min" et ajoute dans le sous-arbre gauche si condition respectée
    if (nouvelle_etape->distance_max_min < root->distance_max_min) {
        root->gauche = insertAVLNode(root->gauche, nouvelle_etape);
    } 
    // Compare les "distance_max-distance_min" et ajoute dans le sous-arbre droit si condition respectée
    else if (nouvelle_etape->distance_max_min >= root->distance_max_min) {
        root->droite = insertAVLNode(root->droite, nouvelle_etape);
    }

    // Mise à jour la hauteur du noeud actuel
    root->hauteur = 1 + max(height(root->gauche), height(root->droite));

    // Obtention du facteur d'équilibre du noeud
    int balance = getBalance(root);

    // Si cas de déséquilibre à gauche, rotation
    if (balance > 1) {
        if (nouvelle_etape->distance_max_min < root->gauche->distance_max_min) {
            return rotateRight2(root);
        } else if (nouvelle_etape->distance_max_min >= root->gauche->distance_max_min) {
            root->gauche = rotateLeft2(root->gauche);
            return rotateRight2(root);
        }
    }

    // Si cas de déséquilibre à droite, rotation
    if (balance < -1) {
        if (nouvelle_etape->distance_max_min >= root->droite->distance_max_min) {
            return rotateLeft2(root);
        } else if (nouvelle_etape->distance_max_min < root->droite->distance_max_min) {
            root->droite = rotateRight2(root->droite);
            return rotateLeft2(root);
        }
    }

    return root;
}

// Fonction recherchant le plus petit noeud à gauche
EtapeAVL *rechercherPlusPetit(EtapeAVL *racine) {
    // Parcours vers le plus à gauche
    while (racine != NULL && racine->gauche != NULL) {
        racine = racine->gauche;
    }
    return racine;
}

EtapeAVL *mettreAJourHauteurEquilibre(EtapeAVL *racine) {
    if (racine == NULL) {
        return NULL;
    }

    // Mise à jour de la hauteur du noeud actuel
    racine->hauteur = 1 + max(height(racine->gauche), height(racine->droite));

    // Calculer le facteur d'équilibre
    int balance = getBalance(racine);

    // Cas de déséquilibre à gauche
    if (balance > 1) {
        if (getBalance(racine->gauche) >= 0) {
            // Cas de la rotation simple à droite
            return rotateRight2(racine);
        } else {
            // Cas de la double rotation gauche-droite
            racine->gauche = rotateLeft2(racine->gauche);
            return rotateRight2(racine);
        }
    }

    // Cas de déséquilibre à droite
    if (balance < -1) {
        if (getBalance(racine->droite) <= 0) {
            // Cas de la rotation simple à gauche
            return rotateLeft2(racine);
        } else {
            // Cas de la double rotation droite-gauche
            racine->droite = rotateRight2(racine->droite);
            return rotateLeft2(racine);
        }
    }

    return racine;
}

EtapeAVL *supprimerPlusPetit(EtapeAVL *racine) {
    // Cas de base : arbre vide
    if (racine == NULL) {
        return NULL;
    }

    // Trouver le plus petit noeud (le plus à gauche)
    if (racine->gauche != NULL) {
        racine->gauche = supprimerPlusPetit(racine->gauche);
    } else {
        // Le plus petit nœud est trouvé, le supprimer
        EtapeAVL *temp = racine->droite;
        free(racine);
        return temp;
    }

    return racine;
}

// Fonction pour insérer tous les noeuds de la liste dans l'arbre AVL
EtapeAVL *insertAVLFromList(Trajet *pliste, EtapeAVL *arbre) {
    Trajet *tmp = pliste;
    int compter = 0;
    while (tmp != NULL) {
        if ( compter >= 50){
            // Si la distance max min supérieur au plus petit de l'arbre, on l'intègre
            if(rechercherPlusPetit(arbre)->distance_max_min < tmp->noeud->distance_max_min){
                arbre = supprimerPlusPetit(arbre);
                arbre = mettreAJourHauteurEquilibre(arbre);
                arbre = insertAVLNode(arbre, tmp->noeud);
            }
            //arbre = mettreAJourHauteurEquilibre(arbre);
        }
        else{
            arbre = insertAVLNode(arbre, tmp->noeud);
        }
        compter ++;
        tmp = tmp->next;
    }
    return arbre;
}

// Fonction auxiliaire pour parcourir l'arbre et remplir le tableau
void fillSortedDataDecreasing(struct EtapeAVL* node, struct EtapeAVL* sortedData[50], int* currentIndex) {
    if (node != NULL && *currentIndex < 50) {
        fillSortedDataDecreasing(node->droite, sortedData, currentIndex);

        // Comparaison avec le pointeur node
        if (*currentIndex < 50) {
            sortedData[*currentIndex] = node;
            *currentIndex = *currentIndex + 1;
        }

        fillSortedDataDecreasing(node->gauche, sortedData, currentIndex);
    }
}



// Fonction pour libérer la mémoire allouée pour chaque élément de sortedData
void freeSortedData(struct EtapeAVL* sortedData[50], int currentIndex) {
    for (int i = 0; i < currentIndex; ++i) {
        free(sortedData[i]);
    }
}

// Fonction pour traiter les statistiques et générer le fichier de sortie
void processStats(struct EtapeAVL* root, FILE* fichier) {
    // Tableau pour stocker les données triées
    struct EtapeAVL* sortedData[50];
    int currentIndex = 0;

    // Fonction auxiliaire pour parcourir l'arbre et remplir le tableau
    fillSortedDataDecreasing(root, sortedData, &currentIndex);

    // Afficher les statistiques et générer les données pour le graphique
    fprintf(fichier, "#ID Distance_mini Distance_moyenne Distance_maxi Distance_max-Distance_min\n");
    for (int i = 0; i < currentIndex; ++i) {
        fprintf(fichier, "%d %.2lf %.2lf %.2lf %.2lf\n", sortedData[i]->id_trajet, sortedData[i]->distance_min, sortedData[i]->distance_moyenne, sortedData[i]->distance_max, sortedData[i]->distance_max_min);
    }

    // Libération de la mémoire allouée pour chaque élément de sortedData
    freeSortedData(sortedData, currentIndex);
}



