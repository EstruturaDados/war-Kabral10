// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TOTAL_TERRITORIOS 5
#define TAM_STRING 100


// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct{
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int numeroTropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.

// Funções de setup e gerenciamento de memória:
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarTerritorios(Territorio territorios[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio %d\n", i + 1);

        /* Nome */
        printf("Nome: ");
        if (fgets(territorios[i].nome, TAM_STRING, stdin) == NULL) {
            /* Se EOF, coloca string vazia */
            territorios[i].nome[0] = '\0';
        } else {
            territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        }

        /* Cor do Exército */
        printf("Cor do Exercito: ");
        if (fgets(territorios[i].cor, TAM_STRING, stdin) == NULL) {
            territorios[i].cor[0] = '\0';
        } else {
            territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';
        }

        /* Número de Tropas (validação: inteiro >= 0) */
        int tmp;
        while (1) {
            printf("Numero de Tropas: ");
            if (scanf("%d", &tmp) != 1) {
                /* leitura falhou (ex.: texto) -> limpar e pedir de novo */
                printf("Entrada invalida. Digite um numero inteiro.\n");
                limparBufferEntrada();
                continue;
            }
            if (tmp < 0) {
                printf("Numero de tropas não pode ser negativo. Tente novamente.\n");
                limparBufferEntrada();
                continue;
            }
            territorios[i].numeroTropas = tmp;
            limparBufferEntrada(); /* consome o '\n' após o número */
            break;
        }

        printf("\n");
    }
}

// Funções de interface com o usuário:
void exibirMapa(const Territorio territorios[], int tamanho) {
    printf("=== Estado Atual do Mapa ===\n\n");
    printf("%-20s %-20s %-10s\n", "Nome", "Cor do Exercito", "Tropas");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        printf("%-20s %-20s %-10d\n",
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].numeroTropas);
    }
}
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main(void) {
    // 1. Configuração Inicial (Setup):

    // - Define o locale para português.
    //setlocale(LC_ALL, "portuguese");

    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    Territorio territorios[TOTAL_TERRITORIOS];

    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.

    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).



    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    printf("=== Cadastro Inicial dos Territorios ===\n\n");
    cadastrarTerritorios(territorios, TOTAL_TERRITORIOS);
    printf("\n");
    exibirMapa(territorios, TOTAL_TERRITORIOS);
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
