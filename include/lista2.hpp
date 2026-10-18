// Declarações da Lista 2 (Estruturas de Dados e Algoritmos).
#pragma once

class No {
public:
    int valor;
    No* esq;
    No* dir;
};

class Arvore {
public:
    No* raiz;
};

// Questão 2 — heap (MAX-heap em vetor, índices a partir de 0)
auto removeMax(int* heap, int N) -> int;                // 2(a) retorna o removido; novo tamanho = N-1
auto insereHeap(int valor, int* heap, int N) -> void;   // 2(b) novo tamanho = N+1

// Questão 3 — árvore binária (recebem o nó; para a árvore toda passe arvore.raiz)
auto somaFolhas(No* no) -> int;             // 3(a)
auto posOrdem(No* no) -> void;              // 3(b)
auto emOrdem(No* no) -> void;               // 3(c)
auto preOrdem(No* no) -> void;              // 3(d)
auto altura(No* no) -> int;                 // 3(e)
auto fatorBalanceamento(No* no) -> int;     // 3(f)
auto emNiveis(No* no) -> void;              // 3(g)
auto produtoNos(No* no) -> long long;       // 3(h)
