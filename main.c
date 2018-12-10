#include <stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct {
    long long int cnp;
    int age, salary;
    char *name;
} Employee;


void adaugaAngajati() {
    FILE *out;
    Employee employee;
    char auxName[20];
    out = fopen("angajati.bin", "wb");

    int numberOfEmployees;
    printf("Introduceti numarul de angajati: ");
    scanf("%d", &numberOfEmployees);
    for (int i = 0; i < numberOfEmployees; i++) {
        printf("Introduceti CNP: ");
        scanf("%llu", &employee.cnp);
        printf("Introduceti numele: ");
        scanf("%s", auxName);
        employee.name = (char *) malloc(strlen(auxName) + 1);
        strcpy(employee.name, auxName);
        printf("Introduceti salariul: ");
        scanf("%u", &employee.salary);
        printf("Introduceti age:");
        scanf("%d", &employee.age);
        fwrite(&employee, sizeof(Employee), 1, out);
        printf("\n");
        printf("Angajatul introdus este: %llu %s %d %d", employee.cnp, employee.name, employee.salary, employee.age);
    }
    fclose(out);
}

void afisareAngajat(long long int cnp) {
    FILE *in = fopen("..//cmake-build-debug//angajati.bin", "rb");
    if (in == NULL) {
        printf("Fisierul nu a putut fi deschis!");
        exit(0);
    }
    fseek(in, 0, SEEK_END);
    int numberOfEmployees = ftell(in) / sizeof(Employee);
    printf("Numarul de angajati din fisier este: %u", numberOfEmployees);
    rewind(in);
    for (int i = 0; i < numberOfEmployees; i++) {
        int varsta, salariul;
        long long int cnpStruct;
        char nume[20];
        fscanf(in, "%llu%s%u%u", &cnpStruct, nume, &salariul, &varsta);
        printf("%llu %s %u %u\n",cnp, nume, varsta, salariul);
        if (cnp == cnpStruct) {
            printf("Nume: %s, varsta: %d, salariul: %d", nume, varsta, salariul);
            int k = 1;
            break;
        }

    }
    fclose(in);

}

//int main() {
////    adaugaAngajati();
//    afisareAngajat(1950201170030);
//    return 0;
//}