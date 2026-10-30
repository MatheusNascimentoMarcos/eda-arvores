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
// COMPLEXIDADE: tempo O(N) por conta das chamadas a função de altura que percorre todos os nós da arvore
auto fator(NoBin* no) -> int {
    if(!no){return 0;}
    
    return altura(no->esq) - altura(no->dir);
}

// 10) Dado um nó DESBALANCEADO, imprime qual rotação é necessária.
//     Imprima EXATAMENTE um destes códigos (nada além dele):
//        LL = esquerda-esquerda  -> rotação simples à direita
//        RR = direita-direita    -> rotação simples à esquerda
//        LR = esquerda-direita   -> rotação dupla à direita
//        RL = direita-esquerda   -> rotação dupla à esquerda
// PROPOSTA:
// COMPLEXIDADE: tempo O(N) por conta das chamadas a função fator
auto qualRotacao(NoBin* no) -> void {
    if (fator(no) == 2) {
        if (fator(no->esq) >= 0) {printf("LL\n");}
        else {printf("LR\n");}
    } else { // fator(no) == -2
        if (fator(no->dir) <= 0) {printf("RR\n");}
        else {printf("RL\n");}
    }
    
}
