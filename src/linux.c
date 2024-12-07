#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para a função sleep
#include <string.h>
#include "Desenho.c"
#ifdef MODO
    #if MODO == 1
        #include "Interface.c"
    #endif
#endif
/*Comando para compilar com o GTK3 (Precisa estar na pasta src do projeto):
    gcc -o Nome_Programa linux.c -D MODO=1 `pkg-config --cflags --libs gtk+-3.0`

  Comando para compilar sem o GTK3:
    gcc -o Nome_Programa linux.c -D MODO=0 

  Comando para executar:
    ./Nome_Programa
*/
FILE* menu_arquivo();
char* Obtem_caminho();
void menu_processamento();

int main(){
    int opcao;
    int infos[3];
    char* caminho = NULL;
    FILE* arquivo = NULL;
    labirinto tabuleiro = NULL;
    int recMax=0,recNum=0;

    do{
        printf("\033[2J\033[1;1H"); //Limpa a tela
        printf("╔══════════════════════════════════╗\n");
        printf("║        PROGRAMA LABIRINTO        ║\n");
        printf("╠══════════════════════════════════╣\n");
        printf("║ 1. Carregar novo arquivo         ║\n");
        printf("║ 2. Processar e exibir respostas  ║\n");
        printf("║ 3. Mostrar desenho do labirinto  ║\n");
        printf("║ 4. Modo análise                  ║\n");
        printf("║ 5. Gerar labirinto em arquivo    ║\n");
        printf("║ 6. Sair                          ║\n");
        printf("╚══════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                
                #ifdef MODO
                    #if MODO == 1
                        caminho = select_file();
                    #elif MODO == 0
                        caminho = Obtem_caminho();
                    #endif
                #endif

                arquivo = menu_arquivo(caminho);

                //printf("\033[2J\033[1;1H"); //Limpa a tela
                menu_processamento(2);
                break;
            case 2:
                if (arquivo != NULL) {
                    //printf("\033[2J\033[1;1H"); //Limpa a tela
                    recNum = 0;
                    recMax = 0;
                    
                    if (tabuleiro != NULL) { //Se ja teve algum processamento anterior
                        fclose(arquivo);
                        arquivo = fopen(caminho, "r");
                    }
                    else {
                        menu_processamento(2);
                    }
                        
                    ordem_matriz ordem;
                    int inicio[2] = {-1, -1};

                    tabuleiro = Processar_Arquivo(arquivo,infos, &ordem);
                    printf("Ordem Matriz: %d %d\n", ordem.linhas, ordem.colunas);
                    
                    Obtem_inicio(tabuleiro, &ordem, inicio);
                    if (inicio[0] == -1 || inicio[1] == -1) {
                        printf("O arquivo de entrada não possui a informação da posição de início\n");
                        printf("Selecione um arquivo válido\n");
                        sleep(1);
                        continue;
                    }
                    
                    estudante *aluno = criaEstudante(infos[2], inicio[0], inicio[1]);
                    const int resultado = Movimenta_estudante(tabuleiro, aluno, ordem, &recMax, &recNum, 0); //Backtracking();

                    if(resultado) {
                        printf("O estudante se movimentou %d vezes e chegou na coluna %d da primeira linha\n", aluno->qtde_movimentos, aluno->coluna_atual+1);
                    }else {
                        printf("O estudante se movimentou %d vezes e percebeu que o labirinto nao tem saida.\n", aluno->qtde_movimentos);
                    }
                    printf("Pressione a tecla enter para voltar ao menu...\n");
                    while (getchar() != '\n'); // Limpa o buffer
                    getchar(); // Aguarda uma tecla

                    free(aluno);
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
                    Labirinto_Grafico(infos[0],infos[1],tabuleiro,false);
                    break;
                }
                else {
                    printf("Labirinto não processado!\n");
                    sleep(1);
                    continue;
                }
            case 4:
                printf("--------------------------------\n");
                printf("MODO ANALISE:\n  Chamadas Recursivas: %d\n  Nivel maximo recursividade: %d\n", recNum, recMax);
                printf("--------------------------------\n");
                printf("Pressione a tecla enter para voltar ao menu...\n");
                while (getchar() != '\n'); // Limpa o buffer
                getchar(); // Aguarda uma tecla
                break;
            case 5:
                int linhas, colunas, num_chaves;
                printf("Digite o número de linhas: ");
                scanf("%d", &linhas);
                printf("Digite o número de colunas: ");
                scanf("%d", &colunas);
                printf("Digite o número de chaves: ");
                scanf("%d", &num_chaves);

                #ifdef MODO
                    #if MODO == 1
                        //Criar uma função para salvar arquivo em GTK3
                        gerar_labirinto(linhas,colunas,num_chaves,select_folder_and_create_file());
                    #else
                        //gerar_labirinto(linhas,colunas,num_chaves,Obtem_caminho());//Versão Terminal
                        gerar_labirinto(linhas,colunas,num_chaves,Obtem_caminho());
                    #endif
                #endif

                break;
            default:
                printf("Saindo...\n");
                exit(1);
                break;
        }
    }while(1);
}

void menu_processamento(int tempo_total){
    const int largura_barra = 50; // Largura da barra de progresso
    printf("Carregando...\n");
    for (int i = 0; i <= largura_barra; i++) {
        printf("\r[");
        for (int j = 0; j < largura_barra; j++) {
            if (j < i)
                printf("=");
            else
                printf(" ");
        }
        printf("] %d%%", (i * 100) / largura_barra);
        fflush(stdout); // Garante que a barra é atualizada no terminal
        usleep((tempo_total * 1000000) / largura_barra); // Divide a duração total igualmente
    }
    printf("\nConcluído!\n");
}

char* Obtem_caminho(){
    char* caminho = (char*)malloc(256 * sizeof(char));
    if (caminho == NULL) {
        perror("Erro ao alocar memória\n");
        exit(1);
    }
    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);
    return caminho;
}


FILE* menu_arquivo(char *caminho){
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo\n");
    }
    return arquivo;
}
