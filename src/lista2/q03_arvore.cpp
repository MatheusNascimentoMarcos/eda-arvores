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
// COMPLEXIDADE: O(N)  passando pelos N nós da árvore para se chegar na folha onde em cada nó tem custo O(1), logo O(n)
auto somaFolhas(No* no) -> int {
    if (!no){
        return 0;
    }
    if(!no->esq && !no->dir){
        return no->valor;
    }

    return somaFolhas(no->esq) + somaFolhas(no->dir);
}

// 3(b) Percurso pós-ordem.
// PROPOSTA:
// COMPLEXIDADE: O(N) pós faz a chamada de função para passar por todos os nós da árvore, com operação constante em cada nó O(1), logo O(N).
auto posOrdem(No* no) -> void {
    if (no)
    {
        posOrdem(no->esq);
        posOrdem (no->dir);
        printf("%d ", no->valor);
    }
    else{return;}
}

// 3(c) Percurso em-ordem.
// PROPOSTA:
// COMPLEXIDADE: O(N) pós faz a chamada de função para passar por todos os nós da árvore, com operação constante em cada nó O(1), logo O(N).
auto emOrdem(No* no) -> void {
    if(no){
        emOrdem(no->esq);
        printf("%d ", no->valor);
        emOrdem(no->dir);
    }else{return;}
    
}

// 3(d) Percurso pré-ordem.
// PROPOSTA:
// COMPLEXIDADE: O(N) pós faz a chamada de função para passar por todos os nós da árvore, com operação constante em cada nó O(1), logo O(N).
auto preOrdem(No* no) -> void {
    if(no){
        printf("%d ", no->valor);
        preOrdem(no->esq);
        preOrdem(no->dir);
    }else{return;}
}

// 3(e) Altura de um nó (folha = 1, nulo = 0).
// PROPOSTA:
// COMPLEXIDADE: tempo O(h) no pior caso caso a árvore degenerada em h = N que é o número de nós
auto altura(No* no) -> int {
    if (!no){return 0;}
    int h;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    if(he > hd){
        h= he + 1;
    }else{
        h = hd + 1;
    }
    return h;
}

// 3(f) Fator de balanceamento = altura(esq) - altura(dir). Nó nulo => 0.
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois devido a chamada de altura para sub arvore esq e dir a função no pior caso vai varrer todos os N nós para se chegar na altura de cada subarvore
auto fatorBalanceamento(No* no) -> int {
    if (!no){
        return 0;
    }else{
        return altura(no->esq) - altura(no->dir);
    }  
}

// 3(g) Percorre a árvore em níveis. fiquei em dúvida se a função deve fazer a leitura a partir de qualquer nó de toda arvóre ou só da subarvore a partir do nó raiz passado
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?) dúvida da complexidade deste
void imprimirNivelAtual(No* no, int nivelAtual) {
    if (!no) {
        return;
    }
    
    if (nivelAtual == 1) {
        printf("%d ", no->valor);
    } 
    // Caso contrário, continua descendo reduzindo o contador de nível
    else if (nivelAtual > 1) {
        imprimirNivelAtual(no->esq, nivelAtual - 1);
        imprimirNivelAtual(no->dir, nivelAtual - 1);
    }
}

auto emNiveis(No* no) -> void {
    int h = altura(no);
    for (int i = 1; i <= h; i++) {
        imprimirNivelAtual(no, i);
    }
}

// 3(h) Produto dos valores de todos os nós (árvore vazia = 0).
// PROPOSTA:
// COMPLEXIDADE: O(N) pois vai ter que percorrer N nós fazendo o produto
auto produtoNos(No* no) -> long long {
    if (!no)
    {
        return 1;
    }else{
        return no->valor * produtoNos(no->esq) * produtoNos(no->dir);
    }
}
