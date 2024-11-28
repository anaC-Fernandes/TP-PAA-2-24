
#include <stdio.h>
#include <stdlib.h>

int menu_principal(){
    int opcao;
    do{
        printf("\033[2J\033[1;1H"); //Limpa a tela 
        printf("╔══════════════════════════════════╗\n");
        printf("║        PROGRAMA LABIRINTO        ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║ 1. Carregar novo arquivo         ║\n");
        printf("║ 2. Processar e exibir respostas  ║\n");
        printf("║ 3. Sair                          ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                return 1;
                break;
            case 2:
                //menu_processamento();
                break;
            case 3:
                printf("Saindo...\n");
                exit(1);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(1);
}

FILE* menu_arquivo(){
    char caminho [256];
    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);
    //strcpy(caminho, "/home/Lucas/Documentos/Codes/C/Trabalhos/TP-PAA-2-24/lib/labirinto.txt");
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
    return arquivo;
}