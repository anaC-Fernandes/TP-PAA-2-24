#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para a função sleep
#include "Desenho.h"
#include <string.h>


FILE* menu_arquivo();
void menu_processamento();

int main(){
    int opcao;
    int infos[3];
    FILE* arquivo = NULL;
    labirinto tabuleiro = NULL;
    int recMax=0,recNum=0;

    do{
        //printf("\033[2J\033[1;1H"); //Limpa a tela
        printf("╔══════════════════════════════════╗\n");
        printf("║        PROGRAMA LABIRINTO        ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║ 1. Carregar novo arquivo         ║\n");
        printf("║ 2. Processar e exibir respostas  ║\n");
        printf("║ 3. Mostrar desenho do labirinto  ║\n");
        printf("║ 4. Modo análise                  ║\n");
        printf("║ 5. Sair                          ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                arquivo = menu_arquivo();
                //menu_processamento(7);
                break;
            case 2:
                if (arquivo != NULL) {
                    //printf("\033[2J\033[1;1H"); //Limpa a tela
                    ordem_matriz ordem;
                    tabuleiro = Processar_Arquivo(arquivo,infos, &ordem);
                    printf("Ordem Matriz: %d %d\n", ordem.linhas, ordem.colunas);
                    estudante *aluno = criaEstudante(0, 9, 4); // pedir o usuário para informar a quantidade de chaves e localização do aluno?
                    const int resultado = Movimenta_estudante(tabuleiro, aluno, ordem, &recMax, &recNum, 0); //Backtracking();
                    printf("Linhas: %d\nColunas: %d\n", aluno->linha_atual, aluno->coluna_atual);
                    //menu_processamento(5);
                    if(resultado) {
                        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha\n", aluno->qtde_movimentos, aluno->coluna_atual+1);
                    }else {
                        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", aluno->qtde_movimentos);
                    }
                    
                    #ifdef ANALISE  
                        #if ANALISE == 1
                            printf("MODO ANALISE:\n  Chamadas Recursivas: %d\n  Nivel maximo recursividade: %d\n", recNum, recMax);
                        #endif
                    #endif
                    recNum = 0;
                    recMax = 0;
                    break;
                }
                else {
                    printf("Arquivo não carregado!\n");
                    sleep(1);
                    continue;;
                }
            case 3:
                printf("\033[2J\033[1;1H"); //Limpa a tela

                if (tabuleiro != NULL) {
                    Labirinto_Grafico(infos[0],infos[1],tabuleiro);
                    break;
                }
                else {
                    printf("Labirinto não processado!\n");
                    sleep(1);
                    continue;
                }
            case 4:
                if (tabuleiro != NULL) {
                    //Modo_Analise();
                    break;
                }
                else {
                    printf("Labirinto não processado!\n");
                    sleep(1);
                    continue;
                }
            case 5:
                printf("Saindo...\n");
                exit(1);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(1);
}

void menu_processamento(int tempo_total){
    // O loop vai simular o progresso do carregamento
    for (int i = 0; i <= tempo_total; i++) {
        // Calcula o progresso como porcentagem
        int progresso = (i * 100) / tempo_total;

        // O \r retorna o cursor para o início da linha, sobrescrevendo o que está nela
        printf("\rCarregando: [");
        
        // Exibe a barra de progresso (com 50 blocos)
        for (int j = 0; j < 50; j++) {
            if (j < progresso / 2)  // Cada 2% de progresso adiciona um bloco
                printf("=");
            else
                printf(" ");
        }

        // Imprime a porcentagem de progresso
        printf("] %d%%", progresso);
        fflush(stdout);  // Garante que a saída seja exibida imediatamente

        // Atraso para simular o progresso (1 segundo por iteração)
        sleep(1);
    }

    // Nova linha após o carregamento
    printf("\nCarregamento concluído!\n");
    sleep(2);
}

FILE* menu_arquivo(){
    char caminho [256];
    /*printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);*/
    //strcpy(caminho, "/mnt/c/Users/gabri/OneDrive/Documentos/GitHub/TP-PAA-2-24/lib/labirinto.txt"); //linux
    strcpy(caminho, "../lib/labirinto.txt");
    FILE* arquivo = fopen(caminho, "r");
    printf("A\n");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo\n");
    }
    return arquivo;
}