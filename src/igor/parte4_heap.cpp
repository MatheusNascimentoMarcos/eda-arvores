// =============================================================================
// Lista do Prof. Igor — Parte IV: Filas de Prioridade  (exercícios 11 e 12)
//
// CONVENÇÕES DOS TESTES: MAX-heap (pai >= filhos), vetor com índices a partir de 0
// (filhos de i: 2i+1 e 2i+2; pai de i: (i-1)/2). N = número de elementos atuais.
// REGRAS: sem o header de algoritmos da STL, sem operator= em classes/agregados,
// discuta a proposta e analise a complexidade.
// Rodar: make p4
// =============================================================================
#include "igor.hpp"
#include "todo.hpp"

// 11) O vetor heap[0..N-1] é um (max-)heap? N = 0 => true.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto ehHeap(int* heap, int N) -> bool {
    TODO();
    return false;
}

// 12) Insere 'elemento' no heap de N elementos (há espaço livre em heap[N]).
//     Ao final o heap tem N+1 elementos.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto novo(int elemento, int* heap, int N) -> void {
    TODO();
}
