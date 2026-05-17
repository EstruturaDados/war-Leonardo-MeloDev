#include <stdio.h>
#include <string.h>

/*
 * 1. Definição da struct:
 * A struct 'Territorio' funciona como um "molde" que agrupa 
 * diferentes tipos de dados (strings e inteiros) pertencentes 
 * a um mesmo contexto lógico.
 */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // 2. Declaração do vetor de structs:
    // Cria um array capaz de armazenar os dados de 5 territórios na memória.
    Territorio mapa[5];

    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");

    /*
     * 3. Laço de entrada de dados:
     * Este 'for' iterará 5 vezes, solicitando e armazenando os dados 
     * em cada posição do vetor 'mapa'.
     */
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastro do Territorio %d ---\n", i + 1);
        
        // Usabilidade: Mensagem clara do que o sistema espera receber.
        printf("Digite o nome do territorio: ");
        // O formato " %29[^\n]" faz o scanf:
        // 1. Ignorar quebras de linha ('\n') residuais no buffer (espaço inicial).
        // 2. Ler até 29 caracteres (deixando 1 para o '\0').
        // 3. Ler nomes compostos com espaços (até o usuário apertar Enter).
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Digite a cor do exercito (ex: Azul): ");
        scanf(" %9[^\n]", mapa[i].cor);

        printf("Digite a quantidade inicial de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n"); // Espaçamento para melhorar a leitura no terminal
    }

    /*
     * 4. Laço de exibição de dados:
     * Percorre o vetor já preenchido e imprime os resultados.
     * A execução desta etapa é imediata após o preenchimento, 
     * cumprindo o requisito de desempenho (< 2 segundos).
     */
    printf("======================================================\n");
    printf("                 RESUMO DOS TERRITORIOS               \n");
    printf("======================================================\n");

    for (int i = 0; i < 5; i++) {
        // Formatação de saída: %-15s garante que o nome ocupe no mínimo 
        // 15 espaços alinhados à esquerda, criando um aspecto visual de tabela.
        printf("[%d] Nome: %-15s | Cor: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    
    printf("======================================================\n");

    return 0;
}