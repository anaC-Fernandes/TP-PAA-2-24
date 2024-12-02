#ifndef ESTUDANTE_H
#define ESTUDANTE_H



#include "Labirinto.h"


typedef struct {
    int quantidade_chave;
    int linha_atual;
    int coluna_atual;
    int qtde_movimentos;
} estudante;

bool Movimenta_estudante(labirinto lab, estudante* aluno, ordem_matriz ordem);
bool Mov_valido(int l, int c, labirinto lab, estudante* aluno, ordem_matriz ordem);



#endif //ESTUDANTE_H