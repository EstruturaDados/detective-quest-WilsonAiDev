#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strcmp e strcpy

// --- ESTRUTURAS DE DADOS ---

/**
 * [NÍVEL NOVATO]
 * Estrutura da Sala (Nó da árvore do mapa).
 */
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * [NÍVEL AVENTUREIRO] [ADAPTAÇÃO VÍDEO 03:44]
 * Estrutura da Pista (Nó da Árvore de Busca Binária - BST).
 * Baseada na 'struct No' do vídeo.
 */
typedef struct Pista {
    char texto[100]; // Texto da pista
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;


// --- FUNÇÕES DO NÍVEL NOVATO (MAPA) ---

/**
 * Aloca e inicializa uma nova Sala.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro critico: Falha ao alocar memoria.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * Constrói o mapa estático da mansão.
 */
Sala* construirMapa() {
    printf("Construindo o mapa da mansao...\n");
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* escritorio = criarSala("Escritorio");
    Sala* sotao = criarSala("Sotao");
    Sala* salaDeJantar = criarSala("Sala de Jantar");

    // Conexões
    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->esquerda = escritorio;
    biblioteca->direita = sotao;
    cozinha->esquerda = salaDeJantar;
    
    printf("Mapa construido com sucesso!\n");
    return hall;
}

/**
 * Libera a memória da árvore do mapa (Pós-ordem).
 */
void liberarMansao(Sala* raiz) {
    if (raiz == NULL) return;
    liberarMansao(raiz->esquerda);
    liberarMansao(raiz->direita);
    free(raiz);
}


// --- FUNÇÕES DO NÍVEL AVENTUREIRO (PISTAS - BST) ---

/**
 * [NÍVEL AVENTUREIRO] [ADAPTAÇÃO VÍDEO 04:15]
 * Aloca e inicializa uma nova Pista.
 * Baseada na função 'criarNo' do vídeo.
 */
Pista* criarPista(const char* texto) {
    Pista* novaPista = (Pista*)malloc(sizeof(Pista));
    if (novaPista == NULL) {
        printf("Erro critico: Falha ao alocar memoria para pista.\n");
        exit(1);
    }
    strcpy(novaPista->texto, texto);
    novaPista->esquerda = NULL;
    novaPista->direita = NULL;
    return novaPista;
}

/**
 * [NÍVEL AVENTUREIRO] [ADAPTAÇÃO VÍDEO 05:06]
 * Insere uma nova pista na Árvore de Busca Binária (BST).
 * A função é recursiva e usa 'strcmp' para manter a ordem alfabética.
 */
Pista* inserirPista(Pista* raiz, const char* textoPista) {
    // 1. Condição de parada: Árvore (ou sub-árvore) vazia.
    // Cria a nova pista aqui.
    if (raiz == NULL) {
        printf("  [Pista encontrada: %s]\n", textoPista);
        return criarPista(textoPista);
    }

    // 2. Comparação de strings (strcmp)
    int comparacao = strcmp(textoPista, raiz->texto);

    // 3. Navegação recursiva
    if (comparacao < 0) {
        // Se a nova pista for "menor" (alfabeticamente), vai para a esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, textoPista);
    } else if (comparacao > 0) {
        // Se a nova pista for "maior", vai para a direita
        raiz->direita = inserirPista(raiz->direita, textoPista);
    } else {
        // Se comparacao == 0, a pista é duplicada.
        printf("  [Pista '%s' ja foi encontrada anteriormente.]\n", textoPista);
    }

    // Retorna a raiz (potencialmente modificada)
    return raiz;
}

/**
 * [NÍVEL AVENTUREIRO] [ADAPTAÇÃO VÍDEO 07:38]
 * Lista todas as pistas em ordem alfabética.
 * Implementa o percurso 'emOrdem' (Esquerda, Raiz, Direita).
 */
void listarPistasEmOrdem(Pista* raiz) {
    if (raiz == NULL) {
        return; // Condição de parada da recursão
    }
    
    // 1. Visita a sub-árvore esquerda (menores)
    listarPistasEmOrdem(raiz->esquerda);
    
    // 2. Visita a Raiz (imprime o valor)
    printf("  - %s\n", raiz->texto);
    
    // 3. Visita a sub-árvore direita (maiores)
    listarPistasEmOrdem(raiz->direita);
}

/**
 * [NÍVEL AVENTUREIRO] [ADAPTAÇÃO VÍDEO 07:58]
 * Libera a memória da árvore de pistas (Pós-ordem).
 */
void liberarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}


// --- LÓGICA PRINCIPAL DO JOGO (MODIFICADA) ---

/**
 * [MODIFICADA]
 * Função de exploração interativa.
 * Agora também gerencia a coleta e visualização de pistas.
 *
 * @param salaAtual O nó do mapa onde o jogador está.
 * @param raizPistas Um ponteiro PARA O PONTEIRO da raiz da BST de pistas.
 * (Usamos Pista** para modificar a raiz original em main).
 */
void explorarSalas(Sala* salaAtual, Pista** raizPistas) {
    if (salaAtual == NULL) {
        printf("A mansao esta vazia.\n");
        return;
    }

    char escolha = ' ';

    while (escolha != 's') {
        printf("\n----------------------------------------\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        printf("----------------------------------------\n");

        // [NOVO] Verifica se há pistas na sala atual
        if (strcmp(salaAtual->nome, "Escritorio") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Carta Rasgada");
        } else if (strcmp(salaAtual->nome, "Sotao") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Diario Antigo");
        } else if (strcmp(salaAtual->nome, "Sala de Jantar") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Frasco de Veneno Vazio");
        }

        // Mostra opções
        printf("Escolha sua acao:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  (e) -> Ir para a Esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  (d) -> Ir para a Direita (%s)\n", salaAtual->direita->nome);
        }
        printf("  (p) -> Ver Pistas Coletadas\n"); // [NOVO] Opção de ver pistas
        printf("  (s) -> Sair da exploracao\n");
        printf("Opcao: ");

        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("\n*** Nao ha caminho para a esquerda. ***\n");
                }
                break;
            case 'd':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("\n*** Nao ha caminho para a direita. ***\n");
                }
                break;
            
            // [NOVO] Case para listar as pistas
            case 'p':
                printf("\n--- SUAS PISTAS (Em ordem alfabetica) ---\n");
                if (*raizPistas == NULL) {
                    printf("  Voce ainda nao encontrou nenhuma pista.\n");
                } else {
                    listarPistasEmOrdem(*raizPistas);
                }
                printf("-------------------------------------------\n");
                break;

            case 's':
                printf("\nSaindo da exploracao...\n");
                break;
            default:
                printf("\n*** Opcao invalida. ***\n");
        }
    }
}

// --- FUNÇÃO MAIN (MODIFICADA) ---
int main() {
    printf("--- Detective Quest: Nivel Aventureiro ---\n");

    // 🌱 Nível Novato: Mapa da Mansão
    Sala* hallDeEntrada = construirMapa();

    // 🔍 Nível Aventureiro: Armazenamento de Pistas
    Pista* arvoreDePistas = NULL; // Inicializa a BST de pistas como vazia

    // Iniciar a exploração (passando a árvore de pistas por referência)
    explorarSalas(hallDeEntrada, &arvoreDePistas);

    // 3. Limpar a memória de AMBAS as árvores
    printf("\nLimpando a memoria do jogo.\n");
    liberarMansao(hallDeEntrada);
    liberarPistas(arvoreDePistas);
    printf("Jogo finalizado.\n");

    // 🧠 Nível Mestre: (Código iria aqui)
    // ...

    return 0;
}