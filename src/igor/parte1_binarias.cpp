// =============================================================================
// Lista do Prof. Igor — Parte I: Estruturas em Árvores Binárias  (exercícios 1.a a 1.h)
//
// REGRAS DO PROFESSOR
//  - Proibido o header de algoritmos da STL (isso inclui max/min!). Escreva você mesmo.
//  - Proibido usar operator= com classes/agregados (só '=' com int, char, ponteiros...).
//  - Discuta a proposta do algoritmo e analise a complexidade (comentários abaixo
//    e/ou docs/igor_discussao.md).
//  - Pode criar funções auxiliares (ex.: 'static') neste arquivo.
//  - Ao implementar uma função, APAGUE o TODO(); dela.
//
// Rodar: make p1        Só um exercício: make p1 ARGS="1c"
// =============================================================================
#include "igor.hpp"
#include "todo.hpp"
#include <cstdio>
// #include <queue>   // STL é permitida (std::queue pode ajudar em 1.b / 1.d)

// 1.a) Estritamente binária: todo nó tem 0 ou 2 filhos. Árvore vazia => true.
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois percorre acessa cada nó da arvore pelo menos uma vez
auto estritaBin(NoBin* no) -> bool {
    if (!no) return true;
    if (!no->esq && !no->dir) return true;
    if (!no->esq || !no->dir) return false;
    return estritaBin(no->esq) && estritaBin(no->dir); 
}

// 1.b) Imprime a árvore em níveis. Imprima SÓ as chaves (separadas por espaço/linha).
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
void imprimirNivelAtual(NoBin* no, int nivelAtual) {
    if (!no) {
        return;
    }
    
    if (nivelAtual == 1) {
        printf("%c ", no->chave);
    } 
    // Caso contrário, continua descendo reduzindo o contador de nível
    else if (nivelAtual > 1) {
        imprimirNivelAtual(no->esq, nivelAtual - 1);
        imprimirNivelAtual(no->dir, nivelAtual - 1);
    }
}

auto emNiveis(NoBin* no) -> void {
    int h = altura(no);
    for (int i = 1; i <= h; i++) {
        imprimirNivelAtual(no, i);
    }
}

// 1.c) Perfeita: todos os nós internos têm 2 filhos e todas as folhas estão no mesmo nível.
//      Árvore vazia => true.
// PROPOSTA:
// COMPLEXIDADE: O(N log N) pois para cada nó é feita verificação da subarvore esq e dir  que corresponde a altura da arvore
auto ehPerfeita(NoBin* no) -> bool {
    if (!no) return true;
    if (altura(no->esq) != altura(no->dir)) return false;
    return ehPerfeita(no->esq) && ehPerfeita(no->dir);
}

// 1.d) Completa: todos os níveis cheios, exceto possivelmente o último, preenchido
//      da esquerda para a direita. Árvore vazia => true.
// PROPOSTA:
// COMPLEXIDADE: ? (dúvida)
auto ehCompleta(NoBin* no) -> bool {
    if (!no) return true;
    int he = altura(no->esq);
    int hd = altura(no->dir);

    if (he == hd)     return ehPerfeita(no->esq) && ehCompleta(no->dir);
    if (he == hd + 1) return ehCompleta(no->esq) && ehPerfeita(no->dir);
    return false;
}

// 1.e) Altura de um nó. CONVENÇÃO usada nos testes: folha = 0 e nó nulo = -1
//      (se preferir folha = 1, mude ALTURA_FOLHA em tests/igor/helpers_igor.hpp).
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois visita cada nó uma vez em ambas as arvores mesmo no pior caso para calculo da altura
auto altura(NoBin* no) -> int {
    if (!no){return 0;}
    int hd = altura(no->dir);
    int he = altura(no->esq);
    if (hd > he)
    {
        return hd + 1;
    }
    else
    {
        return he + 1;
    }
}

// 1.f) Pré-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois percorre cada nó exatamente uma vez
auto preordem(NoBin* no) -> void {
    if(no){
        printf("%c ", no->chave);
        preordem(no->esq);
        preordem(no->dir);
    }else{return;}
}

// 1.g) Pós-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois percorre cada nó exatamente uma vez
auto posordem(NoBin* no) -> void {
    if (no)
    {
        posordem(no->esq);
        posordem(no->dir);
        printf("%c ", no->chave);
    }else
    {
        return;
    }
    
}

// 1.h) In-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) pois percorre cada nó exatamente uma vez
auto inorder(NoBin* no) -> void {
    if(no){
        inorder(no->esq);
        printf("%c ", no->chave);
        inorder(no->dir);
    }else{
        return;
    }
}
