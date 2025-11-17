# 🔍🏛️ Detective Quest — Estruturas de Dados e Investigação

![C](https://img.shields.io/badge/language-C-0078d7?style=flat-square&logo=c)
![Challenge](https://img.shields.io/badge/challenge-Estrutura%20de%20Dados-orange?style=flat-square)
![Status](https://img.shields.io/badge/status-Concluído-success?style=flat-square)

Este é um projeto desenvolvido para a disciplina de Estrutura de Dados. O desafio foi proposto pela **Enigma Studios** e consiste em criar um jogo de mistério interativo onde o jogador explora uma mansão, coleta pistas e investiga suspeitos usando estruturas de dados fundamentais.

O objetivo é propor exercícios práticos em **C** que evoluem por três níveis de complexidade. A abordagem é incremental: cada nível adiciona conceitos e técnicas que reforçam boas práticas de programação e raciocínio algorítmico.

**Estrutura do repositório**

- `algoritimos-novato.c`: Implementação básica com árvore binária para navegação
- `algoritimos-aventureiro.c`: Adiciona BST para organização de pistas
- `algoritimos-mestre.c`: Implementação completa com tabela hash para relacionar pistas e suspeitos
- `README.md`: Documentação do projeto e guia de estudo

**Objetivo do desafio**

Implementar um sistema de investigação funcional em C, utilizando estruturas fundamentais como árvores binárias, árvores de busca binária (BST) e tabelas hash para controlar a lógica de um jogo de detetive interativo.

**Como executar**

Compile e execute cada versão separadamente. Exemplo:

```bash
# Nível Novato
gcc algoritimos-novato.c -o algoritimos-novato
./algoritimos-novato

# Nível Aventureiro
gcc algoritimos-aventureiro.c -o algoritimos-aventureiro
./algoritimos-aventureiro

# Nível Mestre
gcc algoritimos-mestre.c -o algoritimos-mestre
./algoritimos-mestre
```

**Principais temas estudados neste projeto**

- **Árvores Binárias**: Estrutura hierárquica para representação do mapa da mansão
- **Árvores de Busca Binária (BST)**: Armazenamento ordenado de pistas com inserção e busca eficiente
- **Tabelas Hash**: Mapeamento de pistas para suspeitos com função de hash e tratamento de colisões
- **Alocação Dinâmica de Memória**: Uso de `malloc()` e `free()` para gerenciamento eficiente de recursos
- **Estruturas Encadeadas**: Listas encadeadas para resolução de colisões na tabela hash

## 📚 Análise por Nível — O que foi aprendido e utilizado

**Nível Novato** (`algoritimos-novato.c`):

- **O que faz:** Implementa um sistema de navegação básico pela mansão usando árvore binária. O jogador pode explorar cômodos movendo-se para esquerda ou direita a partir do Hall de Entrada.
- **Principais construções usadas:** Estruturas (`struct Sala`), ponteiros para criar relacionamentos entre nós, alocação dinâmica com `malloc()`, recursão para percorrer e liberar árvore.
- **I/O e tratamento de strings:** Interface de linha de comando com `scanf()` para leitura de comandos, `printf()` para exibição de mensagens, uso de `strcmp()` e `strcpy()` para manipulação de strings.
- **Conceitos aprendidos:** Árvore binária não-balanceada, construção estática de estrutura hierárquica, navegação em árvore, gerenciamento manual de memória com liberação recursiva (pós-ordem).

**Nível Aventureiro** (`algoritimos-aventureiro.c`):

- **O que faz:** Expande o nível anterior adicionando um sistema de coleta de pistas. Ao explorar certos cômodos, o jogador encontra pistas que são armazenadas em uma Árvore de Busca Binária (BST), permitindo listagem ordenada alfabeticamente.
- **Principais construções usadas:** Implementação de BST com inserção recursiva, comparação de strings para posicionamento correto na árvore, percurso em-ordem (in-order traversal) para exibição ordenada.
- **I/O e UX:** Menu interativo expandido com opção de visualizar pistas coletadas, detecção de pistas duplicadas, feedback visual ao encontrar novas evidências.
- **Conceitos aprendidos:** Árvore de Busca Binária (BST), inserção ordenada baseada em comparação, percurso em-ordem para ordenação natural, complexidade O(log n) em árvores balanceadas (discussão teórica).

**Nível Mestre** (`algoritimos-mestre.c`):

- **O que faz:** Implementação completa do sistema de investigação. Além da navegação (árvore binária) e coleta de pistas (BST), adiciona uma tabela hash que mapeia pistas a suspeitos. Ao final da exploração, o sistema identifica o suspeito mais citado.
- **Principais construções usadas:** Tabela hash com array de ponteiros, função de hash baseada em soma ASCII, encadeamento para resolução de colisões (lista encadeada), contadores para rastreamento de frequência.
- **Busca e Associação:** Sistema de busca na tabela hash para verificar se suspeito já existe, inserção de pistas em lista encadeada por suspeito, algoritmo para encontrar o suspeito com maior número de evidências.
- **Conceitos aprendidos:** Tabela hash e função de dispersão, tratamento de colisões por encadeamento, complexidade O(1) para inserção/busca (caso ideal), integração de múltiplas estruturas de dados (árvore + hash), análise estatística de dados (suspeito mais citado).

**Observações gerais e boas práticas aplicadas em todo o projeto**

- Gerenciamento rigoroso de memória com funções dedicadas de liberação para cada estrutura (`liberarMansao()`, `liberarPistas()`, `liberarHash()`)
- Verificação de alocação com tratamento de falhas (`if (ptr == NULL) exit(1)`)
- Modularização através de funções específicas para cada operação
- Comentários organizados por seção e nível de complexidade
- Nomenclatura clara e descritiva em português (adequado ao contexto educacional)
- Uso de constantes (`#define TAMANHO_TABELA 10`) para facilitar manutenção
- Interface de usuário consistente entre os níveis, com feedback claro das ações

---

## 🎮 Nível Novato: Mapa da Mansão com Árvore Binária

No nível Novato, você criará a árvore binária que representa o **mapa da mansão**. Cada sala é um nó, e o jogador poderá explorar os caminhos à esquerda ou à direita, começando pelo "Hall de Entrada".

🚩 **Objetivo:** Criar um programa em C que:

- Construa dinamicamente uma árvore binária representando os cômodos.
- Permita que o jogador explore a mansão interativamente (esquerda, direita).
- Exiba o nome de cada cômodo visitado até alcançar um nó-folha (fim do caminho).

⚙️ **Funcionalidades do Sistema:**

- A árvore é criada automaticamente via `main()` com `criarSala()`.
- O jogador interage com o jogo usando `explorarSalas()`, escolhendo entre:
  - `e` → ir para a esquerda
  - `d` → ir para a direita
  - `s` → sair da exploração

📥 **Entrada** e 📤 **Saída de Dados:**

*   O usuário navega pela mansão com base nas opções exibidas no terminal.
*   O programa mostra o nome da sala visitada a cada passo.

**Simplificações para o Nível Novato:**

*   Apenas árvore binária (sem inserção ou remoção durante o jogo).
*   A árvore é montada estaticamente via código.
*   Estrutura imutável em tempo de execução.

---

## 🛡️ Nível Aventureiro: Organização de Pistas com Árvore de Busca

No nível Aventureiro, você expandirá o jogo incluindo uma **árvore de busca (BST)** para armazenar pistas encontradas.

🆕 **Diferença em relação ao Nível Novato:**

*   Agora, ao visitar certos cômodos, o jogador encontrará pistas.
*   Essas pistas são armazenadas ordenadamente em uma BST.

⚙️ **Funcionalidades do Sistema:**

*   Implementar inserção e busca de strings (pistas) na árvore de busca.
*   Permitir que o jogador visualize todas as pistas em ordem alfabética.
*   Adicionar novas pistas automaticamente ao visitar salas específicas.

📥 **Entrada** e 📤 **Saída de Dados:**

*   As pistas são cadastradas via `inserir()` ao serem encontradas.
*   O programa pode listar todas as pistas com `emOrdem()`.

**Simplificações para o Nível Intermediário:**

*   Nenhuma remoção é necessária.
*   Não é necessário balancear a árvore.
*   As pistas são strings simples (nomes curtos).

---

## 🏆 Nível Mestre: Suspeitos e Solução com Tabela Hash

No nível Mestre, você implementará a **tabela hash** para vincular pistas a **suspeitos**. Agora o jogador pode consultar quem está associado a cada pista e deduzir o culpado com base nas evidências coletadas.

🆕 **Diferença em relação ao Nível Aventureiro:**

*   Cada pista armazenada na BST será relacionada a um suspeito via tabela hash.
*   Ao final, o jogador poderá ver qual suspeito está mais associado às pistas e decidir quem é o culpado.

⚙️ **Funcionalidades do Sistema:**

*   Implementar uma tabela hash (array de ponteiros ou lista encadeada).
*   Função de inserção que relaciona pista → suspeito.
*   Permitir consulta de todas as pistas relacionadas a cada suspeito.
*   Mostrar o “suspeito mais citado” ao final da análise.

📥 **Entrada** e 📤 **Saída de Dados:**

*   As pistas e suspeitos são armazenados via `inserirNaHash(pista, suspeito)`.
*   O programa exibe as associações pista → suspeito.
*   Exibe o suspeito mais citado com base nas pistas armazenadas.

**Observações:**

*   Pode utilizar hashing simples com função de espalhamento baseada em primeiros caracteres ou soma ASCII.
*   O ideal é evitar colisões, mas, se ocorrerem, use encadeamento.

---

**Desenvolvido para a disciplina de Estrutura de Dados** 🚀  
*Feito por Wilson Oliveira 💜*
