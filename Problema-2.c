//
// Created by Cosmin Alex on 12/10/2018.
//

#include<stdlib.h>
#include <stdio.h>
#include<string.h>
#include <ctype.h>

typedef struct {
    char *sir;
    int nr_aparitii;
} Cuvant;


void afisare(Cuvant *cuvinte, int *lungimeVector){
    if (cuvinte != NULL)
        for (int i = 0; i < (*lungimeVector); i++) {
            printf("Cuvantul %s apare de %d ori\n", cuvinte[i].sir, cuvinte[i].nr_aparitii);
        }
}

Cuvant *procesareText(int *lungimeVector) {
    FILE *in = fopen("..//cuvinte.txt", "r");
    if (in == NULL) {
        printf("Fisierul nu poate fi deschis");
        exit(0);
    }
    char linie[100];
    *lungimeVector = 0;
    Cuvant *cuvinte = NULL;
    while (fgets(linie, 100, in) != NULL) {
        strtok(linie, "\n");
        char *cuvant;
        cuvant = strtok(linie, " ,.-");
        while (cuvant != NULL) {
            cuvant[0] = (char) tolower(cuvant[0]);
            if (cuvinte == NULL) {
                cuvinte = (Cuvant *) malloc(sizeof(Cuvant));
                cuvinte[0].sir = (char *) malloc(strlen(cuvant) + 1);
                strcpy(cuvinte[0].sir, cuvant);
                cuvinte[0].nr_aparitii = 1;
                (*lungimeVector)++;
            } else {
                int gasit = 0;
                for (int i = 0; i < (*lungimeVector); i++)
                    if (strcmp(cuvinte[i].sir, cuvant) == 0) {
                        cuvinte[i].nr_aparitii++;
                        gasit = 1;
                        break;
                    }

                if (!gasit) {
                    Cuvant *aux = realloc(cuvinte, (*lungimeVector + 1) * sizeof(Cuvant));
                    if (aux != NULL) {
                        cuvinte = aux;
                        cuvinte[(*lungimeVector)].sir = (char *) malloc(strlen(cuvant) + 1);
                        strcpy(cuvinte[(*lungimeVector)].sir, cuvant);
                        cuvinte[(*lungimeVector)].nr_aparitii = 1;
                        (*lungimeVector)++;
                    } else {
                        printf("Nu se poate realoca memoria!");
                    }
                }
            }
            cuvant = strtok(NULL, " ,.-");
        }
    }

    afisare(cuvinte, lungimeVector);

    return cuvinte;
}


int cmp(const void *p, const void *q) {
    Cuvant firstWord = *(Cuvant *) p;
    Cuvant secondWord = *(Cuvant *) q;
    if (firstWord.nr_aparitii > secondWord.nr_aparitii)
        return -1;
    else if (firstWord.nr_aparitii < secondWord.nr_aparitii)
        return 1;
    else return strcmp(firstWord.sir, secondWord.sir);
}

int main() {
    int lungimeVector;
    Cuvant *cuvinte = procesareText(&lungimeVector);
    printf("Vectorul sortat este -------------------------------------\n");
    qsort(cuvinte, lungimeVector, sizeof(Cuvant), cmp);
    afisare(cuvinte, &lungimeVector);
}