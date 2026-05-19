#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Desafio: nível mestre
// Estrutura do Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(const char* missao);
void exibirMapa(Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missaoJ1, char* missaoJ2);

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Atribui uma missão aleatória a um jogador (Passagem por referência simulada via ponteiro)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão do jogador (Passagem por valor, garantida pelo const)
void exibirMissao(const char* missao) {
    printf("Sua missao secreta: %s\n", missao);
}

// Verifica silenciosamente se a condição de vitória foi atingida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    int contAzul = 0, contVermelho = 0;
    int tropasAzul = 0, tropasVermelho = 0;

    // Varre o mapa para coletar o estado atual do jogo
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, "Azul") == 0) {
            contAzul++;
            tropasAzul += mapa[i].tropas;
        } else if (strcmp(mapa[i].cor, "Vermelho") == 0) {
            contVermelho++;
            tropasVermelho += mapa[i].tropas;
        }
    }

    // Avalia a missão com base no estado do mapa
    if (strcmp(missao, "Conquistar 4 territorios") == 0) {
        if (contAzul >= 4 || contVermelho >= 4) return 1;
    } 
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        if (contVermelho == 0) return 1;
    } 
    else if (strcmp(missao, "Eliminar todas as tropas da cor azul") == 0) {
        if (contAzul == 0) return 1;
    } 
    else if (strcmp(missao, "Ter 15 tropas no total") == 0) {
        if (tropasAzul >= 15 || tropasVermelho >= 15) return 1;
    } 
    else if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        if (contAzul >= 3 || contVermelho >= 3) return 1; // Lógica simplificada
    }

    return 0; // Missão ainda não cumprida
}

// Exibe o estado atual do mapa no terminal
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== MAPA ATUAL ===\n");
    for(int i = 0; i < tamanho; i++) {
        printf("[%d] %-12s | Cor: %-8s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==================\n\n");
}

// Lógica de combate baseada em rolagem de dados
void atacar(Territorio* atacante, Territorio* defensor) {
    // Validações antes do combate
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("-> Ataque invalido: Voce nao pode atacar seu proprio territorio.\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("-> Ataque invalido: Tropas insuficientes no territorio atacante.\n");
        return;
    }

    // Rolagem de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("-> Dados Rolados | Atacante: %d vs Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("-> O ATACANTE VENCEU!\n");
        strcpy(defensor->cor, atacante->cor); // Transfere a posse
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;     // Move metade das tropas
        atacante->tropas -= tropasMovidas;
    } else {
        printf("-> O DEFENSOR VENCEU! O atacante perde 1 tropa.\n");
        atacante->tropas--; // Punição por falhar
    }
}

// Limpa toda a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa, char* missaoJ1, char* missaoJ2) {
    free(mapa);
    free(missaoJ1);
    free(missaoJ2);
    printf("\nMemoria liberada com sucesso. Fim de jogo!\n");
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    srand(time(NULL)); // Inicializa a semente de números aleatórios

    // 1. Criação do vetor de missões
    char* bancoDeMissoes[] = {
        "Conquistar 4 territorios",
        "Eliminar todas as tropas da cor vermelha",
        "Eliminar todas as tropas da cor azul",
        "Ter 15 tropas no total",
        "Conquistar 3 territorios seguidos"
    };
    int totalMissoes = 5;

    // 2. Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(4, sizeof(Territorio));
    char* missaoJ1 = (char*) malloc(100 * sizeof(char));
    char* missaoJ2 = (char*) malloc(100 * sizeof(char));

    if (!mapa || !missaoJ1 || !missaoJ2) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Configurando o mapa inicial
    strcpy(mapa[0].nome, "Brasil");    strcpy(mapa[0].cor, "Azul");     mapa[0].tropas = 6;
    strcpy(mapa[1].nome, "Argentina"); strcpy(mapa[1].cor, "Vermelho"); mapa[1].tropas = 3;
    strcpy(mapa[2].nome, "Peru");      strcpy(mapa[2].cor, "Azul");     mapa[2].tropas = 4;
    strcpy(mapa[3].nome, "Colombia");  strcpy(mapa[3].cor, "Vermelho"); mapa[3].tropas = 5;

    // Sorteio das missões
    atribuirMissao(missaoJ1, bancoDeMissoes, totalMissoes);
    atribuirMissao(missaoJ2, bancoDeMissoes, totalMissoes);

    // Interface Inicial
    printf("=== BEM-VINDO AO WAR (SIMULACAO) ===\n");
    printf("\n[Jogador 1 - Azul]\n");
    exibirMissao(missaoJ1);
    
    printf("\n[Jogador 2 - Vermelho]\n");
    exibirMissao(missaoJ2);

    // 3. Simulação interativa (Loop de jogo)
    int vencedor = 0;
    while (!vencedor) {
        exibirMapa(mapa, 4);

        int origem, destino;
        printf("Escolha o indice do territorio ATACANTE e DEFENSOR (ex: 0 1) ou -1 para sair: ");
        scanf("%d", &origem);
        
        if (origem == -1) break;
        
        scanf("%d", &destino);

        if (origem >= 0 && origem < 4 && destino >= 0 && destino < 4) {
            atacar(&mapa[origem], &mapa[destino]);
        } else {
            printf("Indices invalidos.\n");
            continue;
        }

        // 4. Verificação silenciosa de missões
        if (verificarMissao(missaoJ1, mapa, 4)) {
            printf("\n*** JOGADOR 1 (AZUL) CUMPRIU SUA MISSAO E VENCEU O JOGO! ***\n");
            printf("Missao concluida: %s\n", missaoJ1);
            vencedor = 1;
        } else if (verificarMissao(missaoJ2, mapa, 4)) {
            printf("\n*** JOGADOR 2 (VERMELHO) CUMPRIU SUA MISSAO E VENCEU O JOGO! ***\n");
            printf("Missao concluida: %s\n", missaoJ2);
            vencedor = 1;
        }
    }

    // 5. Liberação de memória
    liberarMemoria(mapa, missaoJ1, missaoJ2);

    return 0;
}