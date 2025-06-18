#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define HABILIDADE 5

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d|", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
        }
        printf("\n");
    }
}

// Verifica se posição está dentro do tabuleiro
int dentroDoTabuleiro(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Posiciona navio se não houver sobreposição
int posicionarNavio(int tabuleiro[TAM][TAM], int posicoes[3][2]) {
    for (int i = 0; i < 3; i++) {
        int l = posicoes[i][0];
        int c = posicoes[i][1];
        if (!dentroDoTabuleiro(l, c) || tabuleiro[l][c] != 0) {
            return 0; // posição inválida
        }
    }
    for (int i = 0; i < 3; i++) {
        int l = posicoes[i][0];
        int c = posicoes[i][1];
        tabuleiro[l][c] = NAVIO;
    }
    return 1;
}

// Cria habilidade cone
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= 2 - i && j <= 2 + i) cone[i][j] = 1;
            else cone[i][j] = 0;
        }
    }
}

// Cria habilidade cruz
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }
}

// Cria habilidade octaedro (losango)
void criarOctaedro(int oct[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) oct[i][j] = 1;
            else oct[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int centroL, int centroC) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (matriz[i][j] == 1) {
                int l = centroL + (i - offset);
                int c = centroC + (j - offset);
                if (dentroDoTabuleiro(l, c) && tabuleiro[l][c] == 0) {
                    tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Posiciona navios: 2 normais e 2 diagonais
    int navio1[3][2] = {{1, 1}, {1, 2}, {1, 3}};             // Horizontal
    int navio2[3][2] = {{3, 5}, {4, 5}, {5, 5}};             // Vertical
    int navio3[3][2] = {{6, 6}, {7, 7}, {8, 8}};             // Diagonal principal
    int navio4[3][2] = {{3, 6}, {4, 5}, {5, 4}};             // Diagonal inversa

    posicionarNavio(tabuleiro, navio1);
    posicionarNavio(tabuleiro, navio2);
    posicionarNavio(tabuleiro, navio3);
    posicionarNavio(tabuleiro, navio4);

    // Criação das habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica habilidades em pontos definidos
    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 5, 2);
    aplicarHabilidade(tabuleiro, octaedro, 8, 2);

    // Exibe resultado final
    printf("=== TABULEIRO FINAL ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
