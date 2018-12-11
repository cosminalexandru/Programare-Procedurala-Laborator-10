//
// Created by Cosmin Alex on 12/10/2018.
//

#include <stdlib.h>
#include <stdio.h>

int **fileProcessing(char *fileName, int *m) {
    FILE *in = fopen(fileName, "r");
    if (in == NULL) {
        printf("Nu se poate deschide fisierul!");
        exit(0);
    }
    int **matrix = (int **) malloc(sizeof(int *));

    int numberOfElements, dimension = 1;

    while (fscanf(in, "%d", &numberOfElements) == 1) {
        int **aux = realloc(matrix, dimension * sizeof(int *));
        if (aux == NULL) {
            printf("Nu s-a putut realoca memorie!");
            exit(0);
        } else {
            matrix = aux;
            matrix[dimension - 1] = (int *) malloc((numberOfElements + 1) * sizeof(int));
            matrix[dimension - 1][0] = numberOfElements;
            for (int i = 1; i <= numberOfElements; i++) {
                int element;
                fscanf(in, "%d", &element);
                matrix[dimension - 1][i] = element;
            }
        }
        dimension++;
    }

    fclose(in);
    *m = dimension - 1;
    return matrix;
}

/**
 *
 * @param matrix
 * @param dimension
 */
void afisareMatrice(int **matrix, int dimension) {
    for (int i = 0; i < dimension; i++) {
        if (matrix[i] == NULL) {
            printf("Tablou vid");
        } else {
            printf("%d ", matrix[i][0]);
            for (int j = 1; j <= matrix[i][0]; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

    }
}

/**
 *
 * @param p
 * @param q
 * @return
 */
int cmpElementeTablou(const void *p, const void *q) {
    return *(int *) p - *(int *) q;
}


/**
 *
 * @param matrix
 * @param dimensiune
 * @return
 */
int **sorteazaElementeTablou(int **matrix, int dimensiune) {
    for (int i = 0; i < dimensiune; i++)
        qsort(matrix[i] + 1, matrix[i][0], sizeof(int), cmpElementeTablou);
    return matrix;
}


/**
 *
 * @param a
 * @param b
 * @return
 */
int cmpTablouri(const void *a, const void *b) {
    return *(*(int **) a) - *(*(int **) b);

}

/**
 *
 * @param matrix
 * @param dimension
 * @return
 */
int **sorteazaTablouri(int **matrix, int dimension) {
    qsort(matrix, dimension, sizeof(int *), cmpTablouri);
    return matrix;
}


/**
 *
 * @param matrix
 * @param i
 */
void interclasare(int ***matrix, int i) {
    int *t = (int *) malloc((*matrix)[0][0] * sizeof(int));
    for (int j = 0; j < (*matrix)[0][0] + 1; j++)
        t[j] = (*matrix)[0][j];
    int *aux = realloc((*matrix)[0], (t[0] + (*matrix)[i][0] + 1) * sizeof(int));
    if (aux == NULL) {
        printf("Memorie insuficienta");
        exit(0);
    }
    (*matrix)[0] = aux;
    (*matrix)[0][0] = t[0] + (*matrix)[i][0];

    int a = 1, b = 1, c = 1;
    while (a <= t[0] && b <= (*matrix)[i][0]) {
        if (t[a] < (*matrix)[i][b])
            (*matrix)[0][c++] = t[a++];
        else
            (*matrix)[0][c++] = (*matrix)[i][b++];
    }


    while (a <= t[0]) {
        (*matrix)[0][c++] = t[a++];
    }

    while (b <= (*matrix)[i][0]) {
        (*matrix)[0][c++] = (*matrix)[i][b++];
    }
    (*matrix)[i] = NULL;
    free((*matrix)[i]);
}

/**
 *
 * @param matrix
 * @param dimension
 */
void interclasareMatrice(int ***matrix, int *dimension) {
    for (int i = 1; i < *dimension; i++)
        interclasare(matrix, i);
    *dimension = 1;

}

int main() {

    int dimension, **matrix;
    matrix = fileProcessing("..//numere.txt", &dimension);
    afisareMatrice(matrix, dimension);
    printf("-------------Matricea sortata pe elemente-----------------\n");
    matrix = sorteazaElementeTablou(matrix, dimension);
    afisareMatrice(matrix, dimension);
    printf("-------------Matricea sortata pe tablouri-----------------\n");
    matrix = sorteazaTablouri(matrix, dimension);
    afisareMatrice(matrix, dimension);
    printf("---------Matricea interclasata -------------------\n");
    interclasareMatrice(&matrix, &dimension);
    afisareMatrice(matrix, dimension);
    return 0;
}