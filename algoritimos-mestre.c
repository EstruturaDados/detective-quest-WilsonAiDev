#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strcmp e strcpy

// --- CONFIGURAÇÃO NÍVEL MESTRE ---
#define TAMANHO_TABELA 10 // Define o tamanho da Tabela Hash

// --- ESTRUTURAS DE DADOS ---

// [NÍVEL NOVATO] Nó da árvore do mapa
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// [NÍVEL AVENTUREIRO] Nó da Árvore de Busca Binária (BST) de Pistas
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

// [NÍVEL MESTRE] Nó da lista encadeada de pistas (para a Tabela Hash)
typedef struct PistaListaNode {
    char pista[100];
    struct PistaListaNode* proximo;
} PistaListaNode;

// [NÍVEL MESTRE] Entrada principal da Tabela Hash (usa encadeamento)
typedef struct SuspeitoEntry {
    char nomeSuspeito[50];
    PistaListaNode* pistas; // Lista de pistas associadas a este suspeito
    int contagemPistas;     // Contador para o "mais citado"
    struct SuspeitoEntry* proximo; // Ponteiro para lidar com colisões
} SuspeitoEntry;

// [NÍVEL MESTRE] A Tabela Hash
SuspeitoEntry* tabelaHash[TAMANHO_TABELA];


// --- FUNÇÕES NÍVEL NOVATO (MAPA) ---

Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) exit(1);
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

Sala* construirMapa() {
    printf("Construindo o mapa da mansao...\n");
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* escritorio = criarSala("Escritorio");
    Sala* sotao = criarSala("Sotao");
    Sala* salaDeJantar = criarSala("Sala de Jantar");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;
    biblioteca->esquerda = escritorio;
    biblioteca->direita = sotao;
    cozinha->esquerda = salaDeJantar;
    
    printf("Mapa construido com sucesso!\n");
    return hall;
}

void liberarMansao(Sala* raiz) {
    if (raiz == NULL) return;
    liberarMansao(raiz->esquerda);
    liberarMansao(raiz->direita);
    free(raiz);
}

// --- FUNÇÕES NÍVEL AVENTUREIRO (BST DE PISTAS) ---

// [NÍVEL AVENTUREIRO] Aloca e inicializa uma nova Pista.
Pista* criarPista(const char* texto) {
    Pista* novaPista = (Pista*)malloc(sizeof(Pista));
    if (novaPista == NULL) exit(1);
    strcpy(novaPista->texto, texto);
    novaPista->esquerda = NULL;
    novaPista->direita = NULL;
    return novaPista;
}

// [NÍVEL AVENTUREIRO] Insere uma nova pista na Árvore de Busca Binária (BST).
Pista* inserirPista(Pista* raiz, const char* textoPista) {
    if (raiz == NULL) {
        printf("  [Pista encontrada: %s]\n", textoPista);
        return criarPista(textoPista);
    }
    int comparacao = strcmp(textoPista, raiz->texto);
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, textoPista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, textoPista);
    } else {
         printf("  [Pista '%s' ja foi encontrada.]\n", textoPista);
    }
    return raiz;
}

// [NÍVEL AVENTUREIRO] Lista todas as pistas em ordem alfabética (Percurso emOrdem).
void listarPistasEmOrdem(Pista* raiz) {
    if (raiz == NULL) return;
    listarPistasEmOrdem(raiz->esquerda);
    printf("  - %s\n", raiz->texto);
    listarPistasEmOrdem(raiz->direita);
}

// [NÍVEL AVENTUREIRO] Libera a memória da árvore de pistas (Percurso pós-ordem).
void liberarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

// --- FUNÇÕES NÍVEL MESTRE (TABELA HASH) ---

// Inicializa a tabela hash com valores NULOS.
void inicializarHash() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabelaHash[i] = NULL;
    }
}

// Função de Hashing simples (Soma ASCII)
unsigned int funcaoHash(const char* chave) {
    unsigned long soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_TABELA;
}

// Função 'inserirNaHash' para relacionar pista e suspeito.
void inserirNaHash(const char* pista, const char* suspeito) {
    unsigned int indice = funcaoHash(suspeito);
    SuspeitoEntry* entradaAtual = tabelaHash[indice];

    // 1. Procura se o suspeito já existe nesse índice (tratando colisão)
    while (entradaAtual != NULL) {
        if (strcmp(entradaAtual->nomeSuspeito, suspeito) == 0) {
            // Suspeito encontrado. Adiciona a pista à sua lista.
            
            // Verifica se a pista já foi adicionada a este suspeito
            PistaListaNode* pistaNode = entradaAtual->pistas;
            while (pistaNode != NULL) {
                if (strcmp(pistaNode->pista, pista) == 0) {
                    // Pista já registrada para este suspeito
                    return;
                }
                pistaNode = pistaNode->proximo;
            }

            // Pista é nova para este suspeito
            PistaListaNode* novaPistaNode = (PistaListaNode*)malloc(sizeof(PistaListaNode));
            strcpy(novaPistaNode->pista, pista);
            novaPistaNode->proximo = entradaAtual->pistas; // Adiciona no início da lista
            entradaAtual->pistas = novaPistaNode;
            entradaAtual->contagemPistas++;
            printf("  [Evidencia registrada contra: %s]\n", suspeito);
            return;
        }
        entradaAtual = entradaAtual->proximo; // Próximo na lista de colisão
    }

    // 2. Suspeito não encontrado. Cria uma nova entrada.
    SuspeitoEntry* novaEntrada = (SuspeitoEntry*)malloc(sizeof(SuspeitoEntry));
    strcpy(novaEntrada->nomeSuspeito, suspeito);
    novaEntrada->contagemPistas = 1;

    // Adiciona a primeira pista
    PistaListaNode* novaPistaNode = (PistaListaNode*)malloc(sizeof(PistaListaNode));
    strcpy(novaPistaNode->pista, pista);
    novaPistaNode->proximo = NULL;
    novaEntrada->pistas = novaPistaNode;

    // Adiciona a nova entrada no início da lista de colisão
    novaEntrada->proximo = tabelaHash[indice];
    tabelaHash[indice] = novaEntrada;
    printf("  [Evidencia registrada contra: %s]\n", suspeito);
}

// Lista todas as associações Pista -> Suspeito.
void listarAssociacoes() {
    printf("\n--- RELATORIO DA INVESTIGACAO ---\n");
    int encontrou = 0;
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        SuspeitoEntry* entrada = tabelaHash[i];
        while (entrada != NULL) {
            encontrou = 1;
            printf("SUSPEITO: %s (%d pista(s))\n", entrada->nomeSuspeito, entrada->contagemPistas);
            PistaListaNode* pistaNode = entrada->pistas;
            while (pistaNode != NULL) {
                printf("  -> Pista: %s\n", pistaNode->pista);
                pistaNode = pistaNode->proximo;
            }
            entrada = entrada->proximo;
        }
    }
    if (!encontrou) {
        printf("  Nenhuma pista foi associada a um suspeito ainda.\n");
    }
    printf("----------------------------------\n");
}

// Encontra e exibe o suspeito com o maior número de pistas.
void mostrarSuspeitoMaisCitado() {
    int maxContagem = -1;
    char suspeitoMaisCitado[50] = "Nenhum";

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        SuspeitoEntry* entrada = tabelaHash[i];
        while (entrada != NULL) {
            if (entrada->contagemPistas > maxContagem) {
                maxContagem = entrada->contagemPistas;
                strcpy(suspeitoMaisCitado, entrada->nomeSuspeito);
            }
            entrada = entrada->proximo;
        }
    }

    printf("\n==========================================\n");
    printf("VEREDITO DA INVESTIGACAO\n");
    if (maxContagem > 0) {
        printf("O suspeito mais provavel e: %s\n", suspeitoMaisCitado);
        printf("Com %d pistas associadas a ele.\n", maxContagem);
    } else {
        printf("Nao foi possivel determinar um suspeito.\n");
    }
    printf("==========================================\n");
}

// Libera toda a memória alocada pela Tabela Hash.
void liberarHash() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        SuspeitoEntry* entrada = tabelaHash[i];
        while (entrada != NULL) {
            // Libera a lista interna de pistas
            PistaListaNode* pistaNode = entrada->pistas;
            while (pistaNode != NULL) {
                PistaListaNode* tempPista = pistaNode;
                pistaNode = pistaNode->proximo;
                free(tempPista);
            }
            // Libera a entrada do suspeito
            SuspeitoEntry* tempEntrada = entrada;
            entrada = entrada->proximo;
            free(tempEntrada);
        }
    }
}

// --- LÓGICA PRINCIPAL DO JOGO (MODIFICADA) ---

// Função de exploração interativa.
// Agora gerencia mapa, coleta de pistas (BST) e associações (Hash).
void explorarSalas(Sala* salaAtual, Pista** raizPistas) {
    if (salaAtual == NULL) return;
    char escolha = ' ';

    while (escolha != 's') {
        printf("\n----------------------------------------\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        printf("----------------------------------------\n");

        // Lógica Nível Mestre: Encontra pistas E associa suspeitos
        if (strcmp(salaAtual->nome, "Escritorio") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Carta Rasgada");
            inserirNaHash("Carta Rasgada", "Mordomo");
        } else if (strcmp(salaAtual->nome, "Sotao") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Diario Antigo");
            inserirNaHash("Diario Antigo", "Governanta");
        } else if (strcmp(salaAtual->nome, "Sala de Jantar") == 0) {
            *raizPistas = inserirPista(*raizPistas, "Frasco de Veneno Vazio");
            inserirNaHash("Frasco de Veneno Vazio", "Mordomo");
        }

        // Mostra opções
        printf("Escolha sua acao:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  (e) -> Ir para a Esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  (d) -> Ir para a Direita (%s)\n", salaAtual->direita->nome);
        }
        printf("  (p) -> Ver Pistas Coletadas (Ordem Alfabetica)\n");
        printf("  (c) -> Consultar Associacoes de Suspeitos\n"); // [NOVO]
        printf("  (s) -> Sair da exploracao\n");
        printf("Opcao: ");

        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e': (salaAtual->esquerda != NULL) ? (salaAtual = salaAtual->esquerda) : printf("\n*** Nao ha caminho para a esquerda. ***\n"); break;
            case 'd': (salaAtual->direita != NULL) ? (salaAtual = salaAtual->direita) : printf("\n*** Nao ha caminho para a direita. ***\n"); break;
            case 'p':
                printf("\n--- SUAS PISTAS (Em ordem alfabetica) ---\n");
                (*raizPistas == NULL) ? printf("  Nenhuma pista encontrada.\n") : listarPistasEmOrdem(*raizPistas);
                printf("-------------------------------------------\n");
                break;
            case 'c': // [NOVO]
                listarAssociacoes();
                break;
            case 's': printf("\nSaindo da exploracao...\n"); break;
            default:  printf("\n*** Opcao invalida. ***\n");
        }
    }
}

// --- FUNÇÃO MAIN (COMPLETA) ---

int main() {
    printf("--- Detective Quest: Nivel Mestre ---\n");

    // 🌱 Nível Novato: Mapa da Mansão
    Sala* hallDeEntrada = construirMapa();

    // 🔍 Nível Aventureiro: Armazenamento de Pistas (BST)
    Pista* arvoreDePistas = NULL;

    // 🧠 Nível Mestre: Relações Pista/Suspeito (Hash)
    inicializarHash(); 

    // Iniciar a exploração
    explorarSalas(hallDeEntrada, &arvoreDePistas);

    // Ao final, mostrar o resultado da investigação
    mostrarSuspeitoMaisCitado(); 

    // Limpar a memória de TODAS as estruturas
    printf("\nLimpando a memoria do jogo.\n");
    liberarMansao(hallDeEntrada);   // Libera Árvore do Mapa
    liberarPistas(arvoreDePistas);  // Libera ÁrvORE BST de Pistas
    liberarHash();                  // Libera Tabela Hash
    
    printf("Jogo finalizado.\n");

    return 0;
}