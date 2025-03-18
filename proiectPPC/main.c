#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"   // Windows
#else
    #define CLEAR_SCREEN "clear" // Linux / Mac
#endif

#define MAX_BICYCLES 100
#define MAX_STRING 50

typedef struct {
    char type[MAX_STRING];
    char location[MAX_STRING];
    int available;
} Bicycle;

Bicycle bicycles[MAX_BICYCLES];
int bicycleCount = 0;

void loadBicyclesFromFile() {
    FILE *file = fopen("bicycles.txt", "r");
    if (!file) {
        printf("Eroare: Nu s-a putut deschide fisierul!\n");
        return;
    }

    bicycleCount = 0;
    while (fscanf(file, "%s %s %d", bicycles[bicycleCount].type, bicycles[bicycleCount].location, &bicycles[bicycleCount].available) != EOF) {
        bicycleCount++;
        if (bicycleCount >= MAX_BICYCLES) break;
    }

    fclose(file);
}

void saveBicyclesToFile() {
    FILE *file = fopen("bicycles.txt", "w");
    if (!file) {
        printf("Eroare: Nu s-a putut deschide fisierul pentru scriere!\n");
        return;
    }

    for (int i = 0; i < bicycleCount; i++) {
        fprintf(file, "%s %s %d\n", bicycles[i].type, bicycles[i].location, bicycles[i].available);
    }

    fclose(file);
}

void addBicycle() {
    system(CLEAR_SCREEN);
    printf("===== Adaugare Bicicleta =====\n");

    if (bicycleCount >= MAX_BICYCLES) {
        printf("Lista de biciclete este plina!\n");
        return;
    }

    Bicycle b;
    printf("Introduceti tipul bicicletei: ");
    scanf("%s", b.type);
    printf("Introduceti locatia bicicletei: ");
    scanf("%s", b.location);
    b.available = 1;

    bicycles[bicycleCount] = b;
    bicycleCount++;

    saveBicyclesToFile();
    printf("Bicicleta adaugata cu succes!\n");

    printf("\nApasati Enter pentru a reveni...");
    getchar(); getchar();
}

void viewBicycles() {
    system(CLEAR_SCREEN);
    printf("===== Lista Bicicletelor =====\n");

    if (bicycleCount == 0) {
        printf("Nu exista biciclete in sistem.\n");
    } else {
        for (int i = 0; i < bicycleCount; i++) {
            printf("%d. %s - %s - %s\n", i + 1, bicycles[i].type, bicycles[i].location, bicycles[i].available ? "Disponibila" : "Imprumutata");
        }
    }

    printf("\nApasati Enter pentru a reveni...");
    getchar(); getchar();
}

void borrowBicycle() {
    system(CLEAR_SCREEN);
    printf("===== Imprumutare Bicicleta =====\n");

    viewBicycles();
    if (bicycleCount == 0) return;

    int choice;
    printf("Alegeti numarul bicicletei pentru imprumut (0 pentru back): ");
    scanf("%d", &choice);

    if (choice == 0) return;

    if (choice > 0 && choice <= bicycleCount && bicycles[choice - 1].available) {
        bicycles[choice - 1].available = 0;
        saveBicyclesToFile();
        printf("Bicicleta imprumutata cu succes!\n");
    } else {
        printf("Selectie invalida sau bicicleta nu este disponibila.\n");
    }

    printf("\nApasati Enter pentru a reveni...");
    getchar(); getchar();
}

void returnBicycle() {
    system(CLEAR_SCREEN);
    printf("===== Returnare Bicicleta =====\n");

    viewBicycles();
    if (bicycleCount == 0) return;

    int choice;
    printf("Alegeti numarul bicicletei pentru returnare (0 pentru back): ");
    scanf("%d", &choice);

    if (choice == 0) return;

    if (choice > 0 && choice <= bicycleCount && bicycles[choice - 1].available == 0) {
        bicycles[choice - 1].available = 1;
        saveBicyclesToFile();
        printf("Bicicleta returnata cu succes!\n");
    } else {
        printf("Selectie invalida sau bicicleta nu a fost imprumutata.\n");
    }

    printf("\nApasati Enter pentru a reveni...");
    getchar(); getchar();
}

void showMenu() {
    int option;
    do {
        system(CLEAR_SCREEN);
        printf("======= Meniu Principal =======\n");
        printf("1. Vizualizare biciclete\n");
        printf("2. Adaugare bicicleta\n");
        printf("3. Imprumutare bicicleta\n");
        printf("4. Returnare bicicleta\n");
        printf("5. Iesire\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &option);

        switch (option) {
            case 1: viewBicycles(); break;
            case 2: addBicycle(); break;
            case 3: borrowBicycle(); break;
            case 4: returnBicycle(); break;
            case 5: printf("Iesire...\n"); break;
            default: printf("Optiune invalida!\n");
        }
    } while (option != 5);
}

int main() {
    loadBicyclesFromFile();
    showMenu();
    return 0;
}
