#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// Estrutura do território
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

// --- Protótipos das funções ---
void cadastrarTerritorios(Territorio *territorios, int qtd);
void exibirMapa(Territorio *territorios, int qtd);
void simularBatalha(Territorio *territorios, int atacante, int defensor);

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio *)calloc(QTD_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("=== DESAFIO WAR ESTRUTURADO - NIVEL AVENTUREIRO ===\n\n");

    // Cadastro inicial dos territórios
    cadastrarTerritorios(territorios, QTD_TERRITORIOS);

    int atacante, defensor;
    char continuar;

    // Loop de batalhas
    do {
        exibirMapa(territorios, QTD_TERRITORIOS);

        printf("\nEscolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &atacante);
        printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
        scanf("%d", &defensor);

        if (atacante < 1 || atacante > QTD_TERRITORIOS ||
            defensor < 1 || defensor > QTD_TERRITORIOS || atacante == defensor) {
            printf("❌ Escolha inválida! Tente novamente.\n");
        } else if (territorios[atacante - 1].numeroTropas <= 1) {
            printf("⚠️ O território atacante precisa ter mais de 1 tropa para atacar!\n");
        } else {
            simularBatalha(territorios, atacante - 1, defensor - 1);
        }

        printf("\nDeseja realizar outra batalha? (S/N): ");
        scanf(" %c", &continuar);

    } while (continuar == 'S' || continuar == 's');

    printf("\n=== FIM DAS BATALHAS ===\n");
    exibirMapa(territorios, QTD_TERRITORIOS);

    free(territorios); // libera memória alocada
    return 0;
}

// --- Funções ---

void cadastrarTerritorios(Territorio *territorios, int qtd) {
    getchar(); // limpa buffer do teclado
    for (int i = 0; i < qtd; i++) {
        printf("Cadastro do Território %d:\n", i + 1);

        printf("Nome do Território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numeroTropas);
        getchar();

        printf("\n");
    }
}

void exibirMapa(Territorio *territorios, int qtd) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %-15s | Exército: %-10s | Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numeroTropas);
    }
}

void simularBatalha(Territorio *territorios, int atacante, int defensor) {
    printf("\n🎯 BATALHA ENTRE %s (atacante) E %s (defensor)\n",
           territorios[atacante].nome, territorios[defensor].nome);

    int dadoAtaque = (rand() % 6) + 1;   // 1 a 6
    int dadoDefesa = (rand() % 6) + 1;   // 1 a 6

    printf("Dado do Ataque: %d 🎲\n", dadoAtaque);
    printf("Dado da Defesa: %d 🛡️\n", dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        territorios[defensor].numeroTropas--;

        printf("✅ %s venceu o ataque!\n", territorios[atacante].nome);

        if (territorios[defensor].numeroTropas <= 0) {
            printf("🏴 %s conquistou o território de %s!\n",
                   territorios[atacante].nome, territorios[defensor].nome);
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numeroTropas = 1; // nova tropa mínima
            territorios[atacante].numeroTropas--;   // envia tropa para o território conquistado
        }
    } else {
        printf("🛡️ %s resistiu ao ataque!\n", territorios[defensor].nome);
        territorios[atacante].numeroTropas--; // atacante perde tropa
    }

    printf("\n--- Resultado Parcial ---\n");
    printf("%s: %d tropas\n", territorios[atacante].nome, territorios[atacante].numeroTropas);
    printf("%s: %d tropas\n", territorios[defensor].nome, territorios[defensor].numeroTropas);
}
