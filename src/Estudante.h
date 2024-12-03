#ifndef ESTUDANTE_H
#define ESTUDANTE_H



#include "Labirinto.c"


typedef struct {
    int quantidade_chave;
    int linha_atual;
    int coluna_atual;
    int qtde_movimentos;
} estudante;

bool Movimenta_estudante(labirinto lab, estudante* aluno, ordem_matriz ordem, int* recMax, int* recNum, int n);
bool Mov_valido(int l, int c, labirinto lab, estudante* aluno, ordem_matriz ordem);
estudante *criaEstudante(int qtd_chave, int linha, int coluna);
void Obtem_inicio(labirinto tabuleiro, ordem_matriz* ordem,int *inicio);


#endif //ESTUDANTE_H
