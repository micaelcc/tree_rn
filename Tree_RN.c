#include "Tree_RN.h"

#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

#define NIL_KEY INT_MIN

const int N = 0;
const int R = 1;

NO * NIL;
NO * raiz;

void insertRN(NO * z) {
    NO * y = NIL;
    NO * x = raiz;

    while (x != NIL) {
        y = x;

        if (z->key == x->key) {
            z = NULL;
            x = NIL;
            return;
        } else {
            if (z->key < x->key) {
                x = x->esq;

            } else {
                x = x->dir;

            }
        }
    }

    z->pai = y;

    if (y == NIL) {
        raiz = z;
    } else if (z->key < y->key) {
        y->esq = z;
    } else
        y->dir = z;

    z->esq = NIL;
    z->dir = NIL;
    z->cor = R;

    fix_insert_rn(z);
}

void fix_insert_rn(NO * z) {
    int bool = 0;
    while (z->pai->cor == R) {
        if (z->pai == z->pai->pai->esq) {
            NO * y;
            y = z->pai->pai->dir;

            if (y->cor == R) {
                z->pai->cor = N;
                y->cor = N;
                z->pai->pai->cor = R;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;

                    left_rotate(z);

                    bool = 1;
                }

                z->pai->cor = N;
                z->pai->pai->cor = R;

                right_rotate(z->pai->pai);

            }
        } else if (z->pai == z->pai->pai->dir) {
            NO * y;
            y = z->pai->pai->esq;

            if (y->cor == R) {
                z->pai->cor = N;
                y->cor = N;
                z->pai->pai->cor = R;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;

                    right_rotate(z);

                    bool = 1;
                }

                z->pai->cor = N;
                z->pai->pai->cor = R;

                left_rotate(z->pai->pai);

            }

        }
    }

    raiz->cor = N;

}

void delete_rn(NO * z) {
    if (z == NULL)
        return;

    NO * y = z;
    int corOriginal = y->cor;
    NO * x;
    if (z->esq == NIL) {
        x = z->dir;

        move_parent(z, z->dir);
    } else if (z->dir == NIL) {
        x = z->esq;

        move_parent(z, z->esq);
    } else {
        y = sucessor(z->dir);

        corOriginal = y->cor;

        x = y->dir;

        if (y->pai == z) {
            x->pai = y;
        } else {

            move_parent(y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }

        move_parent(z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    if (corOriginal == N) {
        fix_delete_rn(x);
    }

    free(z);
}

void fix_delete_rn(NO * x) {
    while (x != raiz && x->cor == N) {
        if (x == x->pai->esq) {
            NO * w = x->pai->dir;

            if (w->cor == R) {

                x->pai->cor = R;
                w->cor = N;

                left_rotate(x->pai);

                w = x->pai->dir;

            }

            if (w->esq->cor == N && w->dir->cor == N) {
                w->cor = R;
                x = x->pai;
            } else {
                if (w->dir->cor == N) {

                    w->esq->cor = N;
                    w->cor = R;

                    right_rotate(w);
                    w = x->pai->dir;

                }

                w->cor = x->pai->cor;
                x->pai->cor = N;
                w->dir->cor = N;
                left_rotate(x->pai);
                x = raiz;

            }
        } else {
            NO * w = x->pai->esq;

            if (w->cor == R) {

                x->pai->cor = R;
                w->cor = N;
                right_rotate(x->pai);
                w = x->pai->esq;

            }

            if (w->dir->cor == N && w->esq->cor == N) {
                w->cor = R;
                x = x->pai;
            } else {
                if (w->esq->cor == N) {

                    w->dir->cor = N;
                    w->cor = R;

                    left_rotate(w);
                    w = x->pai->esq;

                }

                w->cor = x->pai->cor;
                x->pai->cor = N;
                w->esq->cor = N;
                right_rotate(x->pai);
                x = raiz;

            }
        }
    }
    x->cor = N;
}

NO * tree_search(int z, NO * pt) {
    while (pt != NULL) {
        if (pt->key == z) {
            return pt;
        }

        if (pt->key > z) {
            pt = pt->esq;
        } else {
            pt = pt->dir;
        }
    }

    return NULL;
}

NO * free_tree(NO * raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    return free_tree(raiz->dir);
    return free_tree(raiz->esq);

    free(raiz);
}

int black_height(NO * pt) {
    int height = 0;

    if (pt != NULL) {
        if (pt->cor == N) {
            int alt_dir = 1 + black_height(pt->dir);
            int alt_esq = 1 + black_height(pt->esq);

            height = (alt_dir > alt_esq) ? alt_dir : alt_esq;

        } else {
            int alt_dir = black_height(pt->dir);
            int alt_esq = black_height(pt->esq);

            height = (alt_dir > alt_esq) ? alt_dir : alt_esq;
        }
    }

    return height;
}

int is_rn(NO * pt) {
    if (pt != NULL) {
        int a = black_height(pt->esq);
        int b = black_height(pt->dir);

        if (a != b) {
            return 0;
        }
        
        return is_rn(pt->esq);
        return is_rn(pt->dir);
    }

    return 1;
}

void move_parent(NO * u, NO * v) {
    if (u->pai == NIL) {
        raiz = v;
    } else {
        if (u == u->pai->esq) {
            u->pai->esq = v;
        } else {
            u->pai->dir = v;
        }
    }

    v->pai = u->pai;
}

NO * sucessor(NO * z) {
    while (z->esq != NIL) {
        z = z->esq;
    }

    return z;
}

NO * create_no(int indice, int Cor) {
    NO * novo = malloc(sizeof(NO));

    novo->key = indice;
    novo->cor = R;
    novo->esq = NIL;
    novo->dir = NIL;
    novo->pai = NIL;

    return novo;
}

void print(NO * pt) {
    if (pt != NULL) {
        if (pt->key != NIL_KEY) {

            if (pt->esq && pt->dir && (pt->esq->key != NIL_KEY && pt->dir->key != NIL_KEY)) {
                printf("(%d) %d | /%d    %d\\\n", pt->cor, pt->key, pt->esq->key, pt->dir->key);
            } else if (pt->esq && pt->esq->key != NIL_KEY) {
                printf("(%d) %d | /%d\n", pt->cor, pt->key, pt->esq->key);
            } else if (pt->dir && pt->dir->key != NIL_KEY) {
                printf("(%d) %d | %d\\\n", pt->cor, pt->key, pt->dir->key);

            } else {
                printf("(%d) %d | Folha\n", pt->cor, pt->key);
            }
        }

        print(pt->esq);
        print(pt->dir);
    }
}

NO * create_tree() {

    return NIL;
}

void left_rotate(NO * z) {
    NO * y;
    y = z->dir;
    z->dir = y->esq;

    if (y->esq != NIL) {
        y->esq->pai = z;
    }

    y->pai = z->pai;

    if (z->pai == NIL)
        raiz = y;
    else if (z == z->pai->esq) {
        z->pai->esq = y;
    } else {
        z->pai->dir = y;
    }

    y->esq = z;

    z->pai = y;

}

void right_rotate(NO * z) {
    NO * y;
    y = z->esq;
    z->esq = y->dir;

    if (y->dir != NIL) {
        y->dir->pai = z;
    }

    y->pai = z->pai;


    if (z->pai == NIL)
        raiz = y;
    else if (z == z->pai->dir) {
        z->pai->dir = y;
    } else {
        z->pai->esq = y;
    }

    y->dir = z;
    z->pai = y;

}

void count_no(NO * pt, int * tam) {
    if (pt != NULL) {
        if (pt->key != NIL_KEY)
            ( * tam) ++;

        count_no(pt->esq, tam);
        count_no(pt->dir, tam);
    }
}
