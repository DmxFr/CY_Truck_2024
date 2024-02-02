
AVL* createAVL(float value, float value2) {
    AVL* avl = safeMalloc(sizeof(AVL));
    avl->value = value;
    avl->value2 = value2;
    avl->left = NULL;
    avl->right = NULL;
    avl->balance = 0;
    return avl;
}

void printAVLInfixRec(AVL* avl) {
    if(avl != NULL) {
        printAVLInfixRec(avl->left);
        printf("%f(%d) ", avl->value, avl->balance);
        printAVLInfixRec(avl->right);
    }
}

void printAVLInfixRec2(AVL* avl) {
    if(avl != NULL) {
        printAVLInfixRec2(avl->left);
        printf("%f - %f\n", avl->value, avl->value2);
        printAVLInfixRec2(avl->right);
    }
}

void parcoursAVL(AVL* avl1, AVL* avl2) { // on parcours l'avl1 (trié par id) pour remplir avl2 (qui va être trié par distance)
    if(avl1 != NULL) {
        parcoursAVL(avl1->left, avl2);
        int a=0;
        insertAVL(avl2, avl1->value2, avl1->value, &a, 0); // inverser les valeurs
        parcoursAVL(avl1->right, avl2);
    }
}

void printAVLInfix(AVL* avl) {
    printAVLInfixRec(avl);
    printf("\n");
}

int heightAVL(AVL* avl) {
    if(avl == NULL) return 0;
    else {
        int leftHeight = heightAVL(avl->left);
        int rightHeight = heightAVL(avl->right);
        return 1 + leftHeight > rightHeight ? leftHeight : rightHeight;
    }
}

AVL* balanceAVL(AVL* avl) {
    if(avl->balance >= -1 && avl->balance <= 1) return avl;
    else if(avl->balance == 2) return avl->right->balance == 1 ? rotateLeft(avl) : rotateDoubleLeft(avl);
    else return avl->left->balance == -1 ? rotateRight(avl) : rotateDoubleRight(avl);
}

AVL* insertAVLRec(AVL* avl, float value, float value2, int* h, int* present, int option) {
    if(avl == NULL) { //Création d'un AVL -> équilibre +- 1
        *h = 1;
        *present = 0;
        return createAVL(value, value2);
    } else if(value == avl->value) { //Noeud déjà présent
        *h = 0;
        *present = 1;
        if(option == 1){
            avl->value2 += value2;
        }
        return avl;
    } else {
        if(value < avl->value) { //Ajouter à gauche
            if(avl->left == NULL){
                avl->left = createAVL(value, value2);
                *present = 0;
            }else{
                avl->left = insertAVLRec(avl->left, value, value2, h, present, option);
            }
            *h = -*h;
        } else { //Ajouter à droite
            if(avl->right == NULL){
                avl->right = createAVL(value, value2);
                *present = 0;
            }else{
                avl->right = insertAVLRec(avl->right, value, value2, h, present, option);
            }
        }

        if(*h != 0) { //Si il y a eu ajout
            avl->balance += *h;
            avl = balanceAVL(avl);
            *h = avl->balance == 0 ? 0 : 1; //Valeur absolue pour éviter la double négation avec l'ajout à gauche
        }
        return avl;
    }
}


AVL* insertAVL(AVL* avl, float value, float value2, int* present, int option) { // value -> pour option -t // value value2 -> pour option -l
    int* h = safeMalloc(sizeof(int));
    *h = 0;
    return insertAVLRec(avl, value, value2, h, present, option);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

AVL* rotateLeft(AVL* avl) { //Rotate the tree to the left
    AVL* root = avl->right;
    avl->right = root->left;
    root->left = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - max(eq_root, 0) - 1;
    root->balance = min(eq_a-2, min(eq_a+eq_root-2, eq_root-1));
    return root;
}

AVL* rotateRight(AVL* avl) { //Rotate the tree to the right
    AVL* root = avl->left;
    avl->left = root->right;
    root->right = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - min(eq_root, 0) + 1;
    root->balance = max(eq_a+2, max(eq_a+eq_root+2, eq_root+1));
    return root;
}

AVL* rotateDoubleLeft(AVL* avl) {
    avl->right = rotateRight(avl->right);
    return rotateLeft(avl);
}

AVL* rotateDoubleRight(AVL* avl) {
    avl->left = rotateLeft(avl->left);
    return rotateRight(avl);
}

