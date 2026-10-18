// =============================================================================
// Lista 2 — Questão 3: árvore binária com class No { int valor; No* esq; No* dir; }
//
// Mesmas regras do Prof. Igor: sem o header de algoritmos da STL (nem max/min),
// sem operator= em classes/agregados, discuta a proposta e a complexidade.
// Funções recebem o nó; para a árvore toda use arvore.raiz.
// Impressões: valores separados por espaço (ex.: "4 2 6 1 3 5 7").
// Convenções dos testes: altura(folha) = 0, altura(nulo) = -1;
//   fatorBalanceamento = altura(esq) - altura(dir); produto da árvore vazia = 1.
// Estas funções também são usadas pelo teste da Questão 1 (make q1).
// Rodar: make q3        Só um item: make q3 ARGS="3e"
// =============================================================================
#include "lista2.hpp"
#include "todo.hpp"
#include <cstdio>

// 3(a) Soma dos valores das folhas.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto somaFolhas(No* no) -> int {
    TODO();
    return 0;
}

// 3(b) Percurso pós-ordem.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto posOrdem(No* no) -> void {
    TODO();
}

// 3(c) Percurso em-ordem.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto emOrdem(No* no) -> void {
    TODO();
}

// 3(d) Percurso pré-ordem.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto preOrdem(No* no) -> void {
    TODO();
}

// 3(e) Altura de um nó (folha = 0, nulo = -1).
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto altura(No* no) -> int {
    TODO();
    return 0;
}

// 3(f) Fator de balanceamento = altura(esq) - altura(dir). Nó nulo => 0.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto fatorBalanceamento(No* no) -> int {
    TODO();
    return 0;
}

// 3(g) Percorre a árvore em níveis.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto emNiveis(No* no) -> void {
    TODO();
}

// 3(h) Produto dos valores de todos os nós (árvore vazia => 1).
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto produtoNos(No* no) -> long long {
    TODO();
    return 1;
}
