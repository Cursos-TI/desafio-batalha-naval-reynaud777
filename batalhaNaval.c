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

// Função para verificar se há sobreposição
int verificarSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int posicoes[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        if (tabuleiro[linha][coluna] != 0) {
            return 1; // sobreposição
        }
    }
    return 0; // livre
}

// Função para posicionar um navio dado um conjunto de coordenadas
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int posicoes[3][2]) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = posicoes[i][0];
        int coluna = posicoes[i][1];
        tabuleiro[linha][coluna] = VALOR_NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = 0;

    // ---- Navio Horizontal ----
    int h_linha = 1, h_coluna = 2;
    if (h_coluna + TAMANHO_NAVIO <= TAMANHO) {
        int horizontal[3][2] = {
            {h_linha, h_coluna},
            {h_linha, h_coluna + 1},
            {h_linha, h_coluna + 2}
        };

        if (!verificarSobreposicao(tabuleiro, horizontal)) {
            posicionarNavio(tabuleiro, horizontal);
        } else {
            printf("Erro: Sobreposição no navio horizontal.\n");
        }
    }

    // ---- Navio Vertical ----
    int v_linha = 4, v_coluna = 0;
    if (v_linha + TAMANHO_NAVIO <= TAMANHO) {
        int vertical[3][2] = {
            {v_linha, v_coluna},
            {v_linha + 1, v_coluna},
            {v_linha + 2, v_coluna}
        };

        if (!verificarSobreposicao(tabuleiro, vertical)) {
            posicionarNavio(tabuleiro, vertical);
        } else {
            printf("Erro: Sobreposição no navio vertical.\n");
        }
    }

    // ---- Navio Diagonal Principal (↘) ----
    int d1_linha = 6, d1_coluna = 6;
    if (d1_linha + TAMANHO_NAVIO <= TAMANHO && d1_coluna + TAMANHO_NAVIO <= TAMANHO) {
        int diagonal1[3][2] = {
            {d1_linha, d1_coluna},
            {d1_linha + 1, d1_coluna + 1},
            {d1_linha + 2, d1_coluna + 2}
        };

        if (!verificarSobreposicao(tabuleiro, diagonal1)) {
            posicionarNavio(tabuleiro, diagonal1);
        } else {
            printf("Erro: Sobreposição no navio diagonal ↘.\n");
        }
    }

    // ---- Navio Diagonal Secundária (↙) ----
    int d2_linha = 2, d2_coluna = 7;
    if (d2_linha + TAMANHO_NAVIO <= TAMANHO && d2_coluna - (TAMANHO_NAVIO - 1) >= 0) {
        int diagonal2[3][2] = {
            {d2_linha, d2_coluna},
            {d2_linha + 1, d2_coluna - 1},
            {d2_linha + 2, d2_coluna - 2}
        };

        if (!verificarSobreposicao(tabuleiro, diagonal2)) {
            posicionarNavio(tabuleiro, diagonal2);
        } else {
            printf("Erro: Sobreposição no navio diagonal ↙.\n");
        }
    }

    // ---- Exibe o Tabuleiro ----
    printf("\nTabuleiro Final:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
