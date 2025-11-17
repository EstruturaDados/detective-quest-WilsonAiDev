#include <stdio.h>
#include <stdlib.h> // Para malloc e free
#include <string.h> // Para strcpy

/**
 * [ADAPTAÇÃO VÍDEO 03:44] [CITE: algoritmos_avancados.c]
 * Estrutura da Sala (Nó da árvore).
 * Conforme sugerido no template, possui nome e ponteiros.
 */
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

/**
 * [ADAPTAÇÃO VÍDEO 04:15] [CITE: algoritmos_avancados.c]
 * Função requisitada 'criarSala'.
 * Aloca dinamicamente e inicializa uma nova sala.
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
 * [APRIMORAMENTO]
 * Função para construir e conectar o mapa estático.
 * Isso limpa a função main() e centraliza a lógica do mapa.
 * Retorna o ponto de início (raiz), o "Hall de Entrada".
 */
Sala* construirMapa() {
    printf("Construindo o mapa da mansao...\n");

    // 1. Criar todas as salas (nós)
    Sala* hall = criarSala("Hall de Entrada");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* salaDeEstar = criarSala("Sala de Estar");
    Sala* escritorio = criarSala("Escritorio");
    Sala* salaDeJantar = criarSala("Sala de Jantar");
    Sala* sotao = criarSala("Sotao"); // Usando a sugestão do .c

    // 2. Conectar as salas (montar a árvore estática)
    //        Hall
    //       /    \
    // Biblioteca  Cozinha
    //   /     \       /
    // Escritorio Sotao  SalaDeJantar
    //
    
    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    biblioteca->direita = sotao;
    
    // Sala de Estar (do código anterior) não foi usada para simplificar
    // o mapa, mas poderia ser adicionada.

    cozinha->esquerda = salaDeJantar;
    // Lado direito da cozinha é NULL (fim de caminho)

    printf("Mapa construido com sucesso!\n");
    return hall; // Retorna a raiz da árvore
}

/**
 * [CITE: README.md, algoritmos_avancados.c]
 * Função requisitada 'explorarSalas'.
 * Permite a navegação interativa (e, d, s) usando um laço.
 */
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        printf("A mansao esta vazia.\n");
        return;
    }

    char escolha = ' ';

    while (escolha != 's') {
        printf("\n----------------------------------------\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        printf("----------------------------------------\n");

        // Verifica se é um nó-folha (fim de caminho)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Este e um fim de caminho. Nao ha mais para onde ir.\n");
        }

        // Mostra opções
        printf("Escolha seu caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  (e) -> Ir para a Esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  (d) -> Ir para a Direita (%s)\n", salaAtual->direita->nome);
        }
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
            case 's':
                printf("\nSaindo da exploracao...\n");
                break;
            default:
                printf("\n*** Opcao invalida. Tente 'e', 'd' ou 's'. ***\n");
        }
    }
}

/**
 * [ADAPTAÇÃO VÍDEO 07:58]
 * Libera recursivamente toda a memória alocada (pós-ordem).
 */
void liberarMansao(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMansao(raiz->esquerda);
    liberarMansao(raiz->direita);
    // printf("Liberando: %s\n", raiz->nome); // (Debug)
    free(raiz);
}

// --- Função Principal ---
// Substitui o conteúdo do arquivo algoritmos_avancados.c
int main() {
    printf("--- Detective Quest: Nivel Novato ---\n");

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    
    // 1. Construir a estrutura da mansão
    Sala* hallDeEntrada = construirMapa();

    // 2. Iniciar a exploração interativa
    explorarSalas(hallDeEntrada);

    // 3. Limpar a memória ao sair
    printf("\nLimpando a memoria da mansao.\n");
    liberarMansao(hallDeEntrada);
    printf("Jogo finalizado.\n");

    // 🔍 Nível Aventureiro: (Código iria aqui)
    // ...

    // 🧠 Nível Mestre: (Código iria aqui)
    // ...

    return 0;
}