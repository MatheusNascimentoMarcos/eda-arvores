// =============================================================================
// Lista do Prof. Igor — Parte II: Árvores Binárias de Busca  (exercícios 2 a 8)
//
// REGRAS: sem o header de algoritmos da STL (nem max/min), sem operator= em
// classes/agregados, discuta a proposta e analise a complexidade.
// Chaves: letras maiúsculas de B..X ('A' = menor possível, 'Z' = maior possível).
// Rodar: make p2        Só um exercício: make p2 ARGS="5"
// =============================================================================
#include "igor.hpp"
#include "todo.hpp"

// 2) Insere 'chave' na BST cuja raiz é 'no' (a raiz já existe, nunca é nula).
//    Nos testes: chave repetida é ignorada (teste "2x").
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto insere(char chave, NoBin* no) -> void {
    TODO();
}

// 3) Maior valor da BST. Árvore vazia => 'A'.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto maior(NoBin* no) -> char {
    TODO();
    return 'A';
}

// 4) Menor valor da BST. Árvore vazia => 'Z'.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto menor(NoBin* no) -> char {
    TODO();
    return 'Z';
}

// 5) Verifica se a árvore binária é uma BST. Árvore vazia => true.
//    Cuidado: comparar só com os filhos diretos não basta!
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto ehBinariaBusca(NoBin* no) -> bool {
    TODO();
    return false;
}

// 6) Busca 'chave'. Retorna a chave se achar, '\0' se não achar.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto busca(char chave, NoBin* no) -> char {
    TODO();
    return '\0';
}

// 7) Elemento imediatamente anterior a 'chave' (maior chave < 'chave'). '\0' se não existir.
//    Nos testes a chave pode NÃO estar na árvore (teste "7x"); mude se discordar.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto anterior(char chave, NoBin* no) -> char {
    TODO();
    return '\0';
}

// 8) Elemento imediatamente posterior a 'chave' (menor chave > 'chave'). '\0' se não existir.
// PROPOSTA:
// COMPLEXIDADE: tempo O(?)  espaço O(?)
auto posterior(char chave, NoBin* no) -> char {
    TODO();
    return '\0';
}
