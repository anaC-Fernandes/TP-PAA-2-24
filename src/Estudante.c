
// Inclusão das bibliotecas
#include "Estudante.h"


// Movimentos (linha, coluna)
int movimentos[4][2] = {
    {-1, 0}, // Cima
    {0, 1},  // Direita
    {0, -1}, // Esquerda
    {1, 0}   // Baixo
};

// Funções já definidas
bool Mov_valido(int l, int c, labirinto lab, estudante* aluno, ordem_matriz ordem) {
    if (l < 0 || l >= ordem.linhas || c < 0 || c >= ordem.colunas) return false; // Fora dos limites
    if (lab[l][c].iswall || lab[l][c].isvisited) return false; // Parede ou já visitado

    if (lab[l][c].isdoor) {
        if (aluno->quantidade_chave > 0) {
            aluno->quantidade_chave--; // Usa a chave
            return true;
        } else {
            return false;
        }
    }
    if (lab[l][c].iskey) {
        aluno->quantidade_chave++; // Pega a chave
    }
    return true;
}

bool Movimenta_estudante(labirinto lab, estudante* aluno, ordem_matriz ordem) {
    if (aluno->linha_atual == 0) return true;

    lab[aluno->linha_atual][aluno->coluna_atual].isvisited = true;

    for (int i = 0; i < 4; i++) {
        int nova_linha = aluno->linha_atual + movimentos[i][0];
        int nova_coluna = aluno->coluna_atual + movimentos[i][1];

        if (Mov_valido(nova_linha, nova_coluna, lab, aluno, ordem)) {
            aluno->linha_atual = nova_linha;
            aluno->coluna_atual = nova_coluna;

            if (Movimenta_estudante(lab, aluno, ordem)) return true;

            aluno->linha_atual -= movimentos[i][0];
            aluno->coluna_atual -= movimentos[i][1];
            aluno->qtde_movimentos++;
        }
    }

    lab[aluno->linha_atual][aluno->coluna_atual].isvisited = false;
    aluno->qtde_movimentos++;
    return false;
}