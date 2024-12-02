#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para a função sleep
#include "Desenho.c"

FILE* menu_arquivo();
void menu_processamento();

int main(){
    int opcao;
    int infos[3];
    FILE* arquivo = NULL;
    labirinto tabuleiro = NULL;

    do{
        printf("\033[2J\033[1;1H"); //Limpa a tela
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
                menu_processamento(7);
                break;
            case 2:
                if (arquivo != NULL) {
                    printf("\033[2J\033[1;1H"); //Limpa a tela
                    tabuleiro = Processar_Arquivo(arquivo,infos);
                    menu_processamento(5);
                    //Backtracking();
                    //Exibir respostas();
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

FILE* menu_arquivo() {
    char nome_arquivo[256];
    char caminho_completo[512]; // Buffer para armazenar o caminho completo
    
    printf("Digite o nome do arquivo (exemplo: labirinto.txt): ");
    scanf("%s", nome_arquivo);
    
    // Prefixar o caminho base ../lib/
    strcpy(caminho_completo, "../lib/");
    strcat(caminho_completo, nome_arquivo);
    
    // Abrir o arquivo
    FILE* arquivo = fopen(caminho_completo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", caminho_completo);
    } else {
        printf("Arquivo aberto com sucesso: %s\n", caminho_completo);
    }
    
    return arquivo;
}