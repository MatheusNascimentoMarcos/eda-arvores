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
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto estritaBin(NoBin* no) -> bool {
    TODO();
    return false;
}

// 1.b) Imprime a árvore em níveis. Imprima SÓ as chaves (separadas por espaço/linha).
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto emNiveis(NoBin* no) -> void {
    TODO();
}

// 1.c) Perfeita: todos os nós internos têm 2 filhos e todas as folhas estão no mesmo nível.
//      Árvore vazia => true.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto ehPerfeita(NoBin* no) -> bool {
    TODO();
    return false;
}

// 1.d) Completa: todos os níveis cheios, exceto possivelmente o último, preenchido
//      da esquerda para a direita. Árvore vazia => true.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto ehCompleta(NoBin* no) -> bool {
    TODO();
    return false;
}

// 1.e) Altura de um nó. CONVENÇÃO usada nos testes: folha = 0 e nó nulo = -1
//      (se preferir folha = 1, mude ALTURA_FOLHA em tests/igor/helpers_igor.hpp).
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto altura(NoBin* no) -> int {
    TODO();
    return 0;
}

// 1.f) Pré-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto preordem(NoBin* no) -> void {
    TODO();
}

// 1.g) Pós-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto posordem(NoBin* no) -> void {
    TODO();
}

// 1.h) In-ordem. Imprima só as chaves.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto inorder(NoBin* no) -> void {
    TODO();
}
