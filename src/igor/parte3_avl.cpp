// =============================================================================
// Lista do Prof. Igor — Parte III: Árvores AVL  (exercícios 9 e 10)
//
// REGRAS: sem o header de algoritmos da STL (nem max/min), sem operator= em
// classes/agregados, discuta a proposta e analise a complexidade.
// Você pode chamar altura() da Parte I (o Makefile já linka os dois arquivos).
// Rodar: make p3
// =============================================================================
#include "igor.hpp"
#include "todo.hpp"
#include <cstdio>

// 9) Fator de balanceamento = altura(esq) - altura(dir). Nó nulo => 0.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto fator(NoBin* no) -> int {
    TODO();
    return 0;
}

// 10) Dado um nó DESBALANCEADO, imprime qual rotação é necessária.
//     Imprima EXATAMENTE um destes códigos (nada além dele):
//        LL = esquerda-esquerda  -> rotação simples à direita
//        RR = direita-direita    -> rotação simples à esquerda
//        LR = esquerda-direita   -> rotação dupla (esq. no filho, depois dir. no nó)
//        RL = direita-esquerda   -> rotação dupla (dir. no filho, depois esq. no nó)
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto qualRotacao(NoBin* no) -> void {
    TODO();
}
