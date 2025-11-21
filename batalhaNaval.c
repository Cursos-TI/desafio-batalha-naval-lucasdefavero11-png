#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro
#define NAVIO 3       // Valor para navio
#define HABILIDADE 5  // Valor para área de efeito
#define SIZE 5        // Tamanho das matrizes das habilidades (5x5)

// ------------------------------------------------------------
// Função: sobrepor habilidade no tabuleiro
// Recebe tabuleiro, matriz de habilidade, ponto de origem.
// ------------------------------------------------------------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int hab[SIZE][SIZE], int origemL, int origemC) {

    // Centro da matriz de habilidade (ex: 5x5 → centro = 2)
    int centro = SIZE / 2;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (hab[i][j] == 1) {  // Só adiciona se a posição for parte da habilidade

                // Coordenadas no tabuleiro
                int linhaT = origemL + (i - centro);
                int colunaT = origemC + (j - centro);

                // Evita sair do tabuleiro
                if (linhaT >= 0 && linhaT < TAM && colunaT >= 0 && colunaT < TAM) {
                    if (tabuleiro[linhaT][colunaT] == 0) {  
                        // Não sobrepõe navio (3), apenas água (0)
                        tabuleiro[linhaT][colunaT] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {

    // ------------------------------------------------------------
    // 1. TABULEIRO — Inicia com 0 (água)
    // ------------------------------------------------------------
    int tabuleiro[TAM][TAM] = {0};

    // ------------------------------------------------------------
    // 2. POSICIONAR NAVIOS (igual nível anterior)
    // ------------------------------------------------------------

    int H_linha = 2, H_coluna = 1;
    int V_linha = 5, V_coluna = 4;
    int D1_linha = 1, D1_coluna = 1;
    int D2_linha = 3, D2_coluna = 7;

    // Horizontal
    for (int i = 0; i < 3; i++) tabuleiro[H_linha][H_coluna + i] = NAVIO;
    // Vertical
    for (int i = 0; i < 3; i++) tabuleiro[V_linha + i][V_coluna] = NAVIO;
    // Diagonal ↘
    for (int i = 0; i < 3; i++) tabuleiro[D1_linha + i][D1_coluna + i] = NAVIO;
    // Diagonal ↙
    for (int i = 0; i < 3; i++) tabuleiro[D2_linha + i][D2_coluna - i] = NAVIO;

    // ------------------------------------------------------------
    // 3. MATRIZES DE HABILIDADES (5x5 cada)
    // Criadas dinamicamente com condicionais.
    // ------------------------------------------------------------

    int cone[SIZE][SIZE];
    int cruz[SIZE][SIZE];
    int octaedro[SIZE][SIZE];

    // ------------------------------------------------------------
    // 3.1 MATRIZ — CONE (apontando para baixo)
    // lógica: quanto mais perto da base, maior a área
    // ------------------------------------------------------------
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            int centro = SIZE / 2;          // centro = 2
            int distancia = centro - i;      // controla expansão
            if (distancia <= 0 && j >= -distancia && j < SIZE + distancia) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // ------------------------------------------------------------
    // 3.2 MATRIZ — CRUZ (linha e coluna do centro são 1)
    // ------------------------------------------------------------
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE/2 || j == SIZE/2) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }

    // ------------------------------------------------------------
    // 3.3 MATRIZ — OCTAEDRO (losango)
    // distância de Manhattan: |i-centro| + |j-centro| <= centro
    // ------------------------------------------------------------
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int dist = (i - SIZE/2 >= 0 ? i-SIZE/2 : SIZE/2-i)
                     + (j - SIZE/2 >= 0 ? j-SIZE/2 : SIZE/2-j);
            if (dist <= SIZE/2) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }

    // ------------------------------------------------------------
    // 4. DEFINIR ORIGENS DAS HABILIDADES
    // ------------------------------------------------------------
    int O_coneL = 4, O_coneC = 2;
    int O_cruzL = 7, O_cruzC = 7;
    int O_octaL = 5, O_octaC = 1;

    // ------------------------------------------------------------
    // 5. APLICAR AS HABILIDADES NO TABULEIRO
    // ------------------------------------------------------------
    aplicarHabilidade(tabuleiro, cone,     O_coneL, O_coneC);
    aplicarHabilidade(tabuleiro, cruz,     O_cruzL, O_cruzC);
    aplicarHabilidade(tabuleiro, octaedro, O_octaL, O_octaC);

    // ------------------------------------------------------------
    // 6. EXIBIR TABULEIRO FINAL
    // ------------------------------------------------------------
    printf("\n===== TABULEIRO FINAL — NIVEL MESTRE =====\n\n");

    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            int valor = tabuleiro[linha][coluna];

            if (valor == 0) printf("~ ");  // água
            else if (valor == 3) printf("# "); // navio
            else if (valor == 5) printf("* "); // habilidade
        }
        printf("\n");
    }

    return 0;
}
