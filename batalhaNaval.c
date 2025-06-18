#include <stdio.h>

#define TAMANHO 10
#define TAMANHO_NAVIO 3
#define VALOR_NAVIO 3

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int c = 0; c < TAMANHO; c++) {
        printf("%d ", c);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa todas as posições com 0 (água)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Define posição inicial do navio horizontal
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    // Verifica se o navio horizontal cabe no tabuleiro
    if (coluna_horizontal + TAMANHO_NAVIO <= TAMANHO) {
        int sobreposicao = 0;

        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_horizontal][coluna_horizontal + i] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_horizontal][coluna_horizontal + i] = VALOR_NAVIO;
            }
        } else {
            printf("Erro: Sobreposição detectada no navio horizontal!\n");
        }
    } else {
        printf("Erro: Navio horizontal fora dos limites!\n");
    }

    // Define posição inicial do navio vertical
    int linha_vertical = 5;
    int coluna_vertical = 6;

    // Verifica se o navio vertical cabe no tabuleiro
    if (linha_vertical + TAMANHO_NAVIO <= TAMANHO) {
        int sobreposicao = 0;

        // Verifica sobreposição
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[linha_vertical + i][coluna_vertical] != 0) {
                sobreposicao = 1;
                break;
            }
        }

        if (!sobreposicao) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[linha_vertical + i][coluna_vertical] = VALOR_NAVIO;
            }
        } else {
            printf("Erro: Sobreposição detectada no navio vertical!\n");
        }
    } else {
        printf("Erro: Navio vertical fora dos limites!\n");
    }

    // Exibe o tabuleiro com navios
    printf("\nTabuleiro Final:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
