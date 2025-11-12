#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

#define CAPACIDADE_MAXIMA 5 // Tamanho fixo da fila, conforme requisito

Peca fila[CAPACIDADE_MAXIMA]; // Array que armazena as peças
int frente = -1; // Posição do primeiro elemento
int tras = -1;   // Posição do último elemento
int id_contador = 0; // Contador global para IDs únicos de novas peças


/**
 * @brief Gera uma nova peça com um tipo aleatório e um ID único.
 * @return A peça gerada.
 */
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L', 'S', 'Z', 'J'}; // Tipos possíveis
    int num_tipos = sizeof(tipos) / sizeof(tipos[0]);

    // Define o tipo da peça aleatoriamente
    novaPeca.nome = tipos[rand() % num_tipos];

    // Define o ID único e incrementa o contador global
    novaPeca.id = id_contador++;

    return novaPeca;
}

/**
 * @brief Verifica se a fila está cheia.
 * @return 1 se cheia, 0 caso contrário.
 */
int estaCheia() {
    // A fila está cheia se o próximo do 'tras' for a 'frente' (operação modular)
    return (tras + 1) % CAPACIDADE_MAXIMA == frente;
}

/**
 * @brief Verifica se a fila está vazia.
 * @return 1 se vazia, 0 caso contrário.
 */
int estaVazia() {
    return frente == -1;
}

// --- Operações da Fila ---

/**
 * @brief Insere uma nova peça no final da fila (enqueue).
 * @param novaPeca A peça a ser inserida.
 */
void inserirPeca(Peca novaPeca) {
    if (estaCheia()) {
        printf("A fila esta cheia! Nao foi possivel inserir a peca [%c %d].\n", novaPeca.nome, novaPeca.id);
    } else {
        if (estaVazia()) {
            frente = 0;
        }
        // Move o 'tras' para a próxima posição circular
        tras = (tras + 1) % CAPACIDADE_MAXIMA;
        fila[tras] = novaPeca;
        printf("-> Peça [%c %d] inserida (Enqueue).\n", novaPeca.nome, novaPeca.id);
    }
}

/**
 * @brief Remove e retorna a peça da frente da fila (dequeue).
 * @return A peça removida.
 */
Peca jogarPeca() {
    Peca pecaRemovida = {'\0', -1}; // Peça nula para indicar erro

    if (estaVazia()) {
        printf("A fila esta vazia! Nao ha pecas para jogar (Dequeue).\n");
    } else {
        pecaRemovida = fila[frente]; // Pega a peça da frente

        if (frente == tras) {
            // Se for o último elemento, a fila volta a ficar vazia
            frente = -1;
            tras = -1;
        } else {
            // Move a 'frente' para a próxima posição circular
            frente = (frente + 1) % CAPACIDADE_MAXIMA;
        }

        printf("-> Peça [%c %d] jogada (Dequeue).\n", pecaRemovida.nome, pecaRemovida.id);
    }
    return pecaRemovida;
}

/**
 * @brief Exibe o estado atual da fila, mostrando todas as peças.
 */
void visualizarFila() {
    if (estaVazia()) {
        printf("\nConfira a seguir seu estado:\n");
        printf("Fila de pecas: [Vazia]\n");
        return;
    }

    printf("\nConfira a seguir seu estado:\n");
    printf("Fila de pecas");

    int i = frente;
    do {
        printf(" [%c %d]", fila[i].nome, fila[i].id);
        if (i == tras) break; // Para quando chegar ao final
        i = (i + 1) % CAPACIDADE_MAXIMA;
    } while (i != (tras + 1) % CAPACIDADE_MAXIMA); // Continua até passar o 'tras'

    printf("\n\n");
}

int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios (para gerarPeca)
    int opcao;

    // 1. Inicializa a fila com 5 elementos fixos
    printf("--- Inicializacao da Fila de Pecas (Capacidade: %d) ---\n", CAPACIDADE_MAXIMA);
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        inserirPeca(gerarPeca());
    }
    visualizarFila();

    // 2. Menu de Ações
    do {
        printf("--- Menu de Acoes ---\n");
        printf("1. Jogar uma peca (Dequeue)\n");
        printf("2. Inserir nova peca (Enqueue)\n");
        printf("3. Visualizar Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                visualizarFila();
                break;
            case 2:
                inserirPeca(gerarPeca());
                visualizarFila();
                break;
            case 3:
                visualizarFila();
                break;
            case 0:
                printf("Encerrando o simulador de fila de pecas.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
