

typedef struct _AVL {
    float value;
    float value2;
    struct _AVL* left;
    struct _AVL* right;
    int balance;
} AVL;

AVL* createAVL(float value, float value2);

void printAVLInfix(AVL* avl);

int heightAVL(AVL* avl);

int getBalanceAVL(AVL* avl);

AVL* balanceAVL(AVL* avl);

AVL* insertAVL(AVL* avl, float value,  float value2, int* present, int option);

AVL* insertAVLRec(AVL* avl, float value, float value2, int* h, int* present, int option);

AVL* rotateLeft(AVL* avl);

AVL* rotateRight(AVL* avl);

AVL* rotateDoubleLeft(AVL* avl);

AVL* rotateDoubleRight(AVL* avl);

