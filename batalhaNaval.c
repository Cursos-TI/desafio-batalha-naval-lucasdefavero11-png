#include <stdio.h>

int main() {

    // -----------------------------
    // 1. DECLARAÇÃO DO TABULEIRO
    // -----------------------------
    // Matriz 10x10 inicializada com água (0)
    int tabuleiro[10][10] = {0};

    // -----------------------------
    // 2. DECLARAÇÃO DOS NAVIOS
    // -----------------------------
    // Cada navio ocupa 3 posições
    int navioHorizontal[3] = {3, 3, 3}; // Navio horizontal
    int navioVertical[3]   = {3, 3, 3}; // Navio vertical

    // -----------------------------
    // 3. COORDENADAS INICIAIS
    // -----------------------------
    // São definidas diretamente no código (simplificação)
    int linhaH = 2; // linha inicial do navio horizontal
    int colunaH = 4; // coluna inicial do navio horizontal

    int linhaV = 5; // linha inicial do navio vertical
    int colunaV = 7; // coluna inicial do navio vertical

    // -----------------------------
    // 4. VALIDAÇÃO SIMPLES DO NAVIO HORIZONTAL
    // -----------------------------
    if (colunaH + 2 >= 10) {
        printf("Erro: navio horizontal sairia do tabuleiro!\n");
        return 1;
    }

    // -----------------------------
    // 5. POSICIONAR NAVIO HORIZONTAL
    // -----------------------------
    for (int i = 0; i < 3; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // -----------------------------
    // 6. VALIDAÇÃO SIMPLES DO NAVIO VERTICAL
    // -----------------------------
    if (linhaV + 2 >= 10) {
        printf("Erro: navio vertical sairia do tabuleiro!\n");
        return 1;
    }

    // -----------------------------
    // 7. VERIFICAR SE HÁ SOBREPOSIÇÃO
    // -----------------------------
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[linhaV + i][colunaV] != 0) {
            printf("Erro: navio vertical sobrepõe outro navio!\n");
            return 1;
        }
    }

    // -----------------------------
    // 8. POSICIONAR NAVIO VERTICAL
    // -----------------------------
    for (int i = 0; i < 3; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // -----------------------------
    // 9. EXIBIR O TABULEIRO COMPLETO
    // -----------------------------
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");

    for (int linha = 0; linha < 10; linha++) {
        for (int coluna = 0; coluna < 10; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]); // imprime linha por linha
        }
        printf("\n");
    }

    return 0;
}
