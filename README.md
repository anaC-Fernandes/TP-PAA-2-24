
# Trabalho Prático 1 - Projeto e Análise de Algoritmos

Este repositório contém o código e a documentação do **Trabalho Prático 1** da disciplina de **Projeto e Análise de Algoritmos** da UFV – Campus Florestal.

## Descrição

O objetivo é implementar um algoritmo de **backtracking** em C para encontrar a saída de um labirinto, conforme especificações fornecidas. O programa utiliza um arquivo de entrada que define o layout do labirinto e as restrições, como paredes e portas que necessitam de chaves.

## Funcionalidades

1. **Carregar Arquivo**: Leitura dos dados do labirinto.
2. **Processar Labirinto**: 
   - Encontrar um caminho da posição inicial até a saída.
   - Exibir o caminho percorrido e o número de movimentos realizados.
   - Detectar quando o labirinto não possui saída.
3. **Modo Análise**: Contabiliza chamadas recursivas e o nível máximo de recursão.

## Como Usar

### Requisitos
- Compilador GCC.

### Passos
1. Clone o repositório:
   ```bash
   git clone https://github.com/seu_usuario/TP-PAA-2-24.git
   ```
2. Compile o programa:
   ```bash
   make
   ```

## Formato do Arquivo de Entrada

- Primeira linha: `<linhas> <colunas> <chaves>`
- Linhas seguintes: Layout do labirinto com:
  - `0`: Posição inicial.
  - `1`: Caminhos livres.
  - `2`: Paredes.
  - `3`: Portas que precisam de chaves.

Exemplo:
```
10 10 1
1111111111
1111111111
2222212222
1111111111
1111111111
3222222111
1111112111
1222222111
1111111111
1111011111
```

## Modo Análise



## Autores

- Ana Carolina Fernandes
-  Gabriel Benez Duarte
-  Lucas Fonseca
- Luiz Felipe Coutinho

