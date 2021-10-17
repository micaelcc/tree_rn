//Definições do TIPO NO e funcoes de Arvore RB

struct no{
    int key;
    int cor;
    struct no * pai;
    struct no * esq;
    struct no * dir;
};

typedef struct no NO;


void insertRN(NO * z);
NO * create_no(int indice, int Cor);
void print(NO * pt);
void count_no(NO * pt, int *tam);
void perc(NO * pt);
void move_parent(NO * u, NO * v);
NO * sucessor(NO * z);
void fix_delete_rn(NO * x);
NO * tree_search(int z, NO * pt);
void delete_rn(NO * z);
NO * free_tree(NO * raiz);
int black_height(NO *pt);
int is_rn(NO * pt);
void fix_insert_rn(NO * z);
void left_rotate(NO * z);
void right_rotate(NO * z);
NO * create_tree();



