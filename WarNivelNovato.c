#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Definição da struct Territorio
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

int main() {
    Territorio territorios[QTD_TERRITORIOS];
    int i;

    printf("=== DESAFIO WAR ESTRUTURADO - NIVEL NOVATO ===\n\n");

    // Cadastro dos 5 territórios
    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        printf("Nome do Território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o \n

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar(); // limpa o buffer do teclado

        printf("\n");
    }

    // Exibição organizada dos dados
    printf("=== ESTADO ATUAL DO MAPA ===\n\n");
    for (i = 0; i < QTD_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome..........: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numeroTropas);
        printf("-------------------------------\n");
    }

    return 0;
}
