#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio: nível aventureiro
/* =========================================
   ESTRUTURA DO TERRITÓRIO
   ========================================= */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* =========================================
   PROTÓTIPOS DAS FUNÇÕES
   ========================================= */
void cadastrar(Territorio* mapa, int quantidade);
void exibir(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

/* =========================================
   FUNÇÃO PRINCIPAL
   ========================================= */
int main() {
    // Inicializa a semente para a geração de números aleatórios
    srand(time(NULL));

    int qtd_territorios;
    printf("=== BEM-VINDO AO WAR ESTRUTURADO ===\n");
    printf("Quantos territorios deseja cadastrar no mapa? ");
    scanf("%d", &qtd_territorios);
    limparBuffer();

    if (qtd_territorios < 2) {
        printf("Para que haja batalhas, cadastre pelo menos 2 territorios!\n");
        return 1;
    }

    // 1. ALOCAÇÃO DINÂMICA
    // Aloca a quantidade necessária de territórios usando calloc para zerar a memória
    Territorio* mapa = (Territorio*) calloc(qtd_territorios, sizeof(Territorio));
    
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrar(mapa, qtd_territorios);

    int opcao;
    do {
        printf("\n=== STATUS DO MAPA ===\n");
        exibir(mapa, qtd_territorios);

        printf("\nO que deseja fazer?\n");
        printf("1 - Realizar um ataque\n");
        printf("0 - Sair e encerrar o jogo\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int id_atacante, id_defensor;
            
            printf("\nSelecione o ID do territorio ATACANTE: ");
            scanf("%d", &id_atacante);
            printf("Selecione o ID do territorio DEFENSOR: ");
            scanf("%d", &id_defensor);

            // Validação básica dos IDs inseridos
            if (id_atacante >= 0 && id_atacante < qtd_territorios && 
                id_defensor >= 0 && id_defensor < qtd_territorios) {
                
                // Passa o endereço de memória dos territórios escolhidos
                atacar(&mapa[id_atacante], &mapa[id_defensor]);
            } else {
                printf("Erro: IDs de territorios invalidos!\n");
            }
        }

    } while (opcao != 0);

    // 4. LIBERAÇÃO DE MEMÓRIA
    liberarMemoria(mapa);
    printf("Memoria liberada com sucesso. Fim de jogo!\n");

    return 0;
}

/* =========================================
   IMPLEMENTAÇÃO DAS FUNÇÕES
   ========================================= */

// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Realiza o cadastro inicial dos territórios
void cadastrar(Territorio* mapa, int quantidade) {
    printf("\n--- CADASTRO DE TERRITORIOS ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio [%d]:\n", i);
        
        printf("Nome do territorio: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = 0; // Remove o '\n' do final

        printf("Cor do exercito (Ex: Vermelho, Azul): ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = 0;

        printf("Numero inicial de tropas: ");
        scanf("%d", &(mapa + i)->tropas);
        limparBuffer();
    }
}

// Exibe o status atual de todos os territórios
void exibir(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("ID [%d] | Territorio: %-15s | Cor: %-10s | Tropas: %d\n", 
               i, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
}

// 2. SIMULAÇÃO DE ATAQUES E 3. ATUALIZAÇÃO DE DADOS
// Resolve a batalha utilizando ponteiros para alterar os dados originais
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- RESOLUCAO DA BATALHA ---\n");
    
    // Regra de Negócio: Não pode atacar a própria cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Acao Invalida: Você nao pode atacar um territorio da sua propria cor!\n");
        return;
    }

    // Regra de Negócio: Precisa de mais de 1 tropa para iniciar um ataque
    if (atacante->tropas <= 1) {
        printf("Acao Invalida: O territorio '%s' nao tem tropas suficientes para atacar (minimo 2)!\n", atacante->nome);
        return;
    }

    // Simulação dos dados de batalha (1 a 6)
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("⚔️ Batalha: %s (Atacante) vs %s (Defensor)\n", atacante->nome, defensor->nome);
    printf("🎲 Dado do Atacante: %d\n", dado_atacante);
    printf("🎲 Dado do Defensor: %d\n", dado_defensor);

    // Avaliação do vencedor
    if (dado_atacante > dado_defensor) {
        printf("🏆 Resultado: ATACANTE VENCEU!\n");
        
        // Atualiza os dados: Transfere cor e metade das tropas
        strcpy(defensor->cor, atacante->cor);
        
        int tropas_transferidas = atacante->tropas / 2;
        defensor->tropas = tropas_transferidas;
        atacante->tropas -= tropas_transferidas;
        
        printf("O territorio '%s' foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
    } else {
        // Empate no dado favorece o defensor no War clássico, então (atacante <= defensor) = defensor vence
        printf("🛡️ Resultado: DEFENSOR VENCEU OU EMPATOU!\n");
        
        // Atacante perde 1 tropa
        atacante->tropas -= 1;
        printf("O ataque falhou. O territorio '%s' perdeu 1 tropa.\n", atacante->nome);
    }
}

// Libera a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
    }
}