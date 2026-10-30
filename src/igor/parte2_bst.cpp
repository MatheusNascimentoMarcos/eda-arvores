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
// COMPLEXIDADE: tempo O(H) no pior caso por percorrer a altura da arvore h = N e no caso da arvore balanceada a cada nível desce um dos 2 nós log h= Log N
auto insere(char chave, NoBin* no) -> void {
    if (chave == no->chave) return;
    if(no->chave < chave){
        if (no->dir){
            insere(chave,no->dir);
        }else{
            no->dir = new NoBin{chave, nullptr, nullptr};
        }
        
    }else{
        if (no->esq){
            insere(chave,no->esq);
        }else{
            no->esq = new NoBin{chave, nullptr, nullptr};
        }
    }
}

// 3) Maior valor da BST. Árvore vazia => 'A'.
// PROPOSTA:
// COMPLEXIDADE: O(h), que é O(n) no pior caso em caso de arvore degenerada para direita.
auto maior(NoBin* no) -> char {
    if(!no){return 'A';}
    while (no->dir)
    {
        no = no->dir;
    }
    return no->chave;
}

// 4) Menor valor da BST. Árvore vazia => 'Z'.
// PROPOSTA:
// COMPLEXIDADE: O(h), que é O(n) no pior caso de arvore degenerada para esquerda.
auto menor(NoBin* no) -> char {
    if(!no){return 'Z';}
    while (no->esq)
    {
        no = no->esq;
    }
    return no->chave;
}

// 5) Verifica se a árvore binária é uma BST. Árvore vazia => true.
//    Cuidado: comparar só com os filhos diretos não basta!
// PROPOSTA:
// COMPLEXIDADE: tempo O(N*h) pois a função percorre todos os nós e para cada no analisa o menor e maior qe temcoplexdade O(h), então no pior caso da arvore degenerar teremos O(N²)
auto ehBinariaBusca(NoBin* no) -> bool {
    if (!no) return true;
    if (no->esq && maior(no->esq) >= no->chave) return false;
    if (no->dir && menor(no->dir) <= no->chave) return false;
    return ehBinariaBusca(no->esq) && ehBinariaBusca(no->dir);
}

// 6) Busca 'chave'. Retorna a chave se achar, '\0' se não achar.
// PROPOSTA:
// COMPLEXIDADE: no pior cenário em caso de av degenerada O(h) e no cenário de av balanceada O(log N) por a cada nivel a gente escoher umentre os 2 nós possíveis
auto busca(char chave, NoBin* no) -> char {
    if(no){
        if (chave == no->chave){
            return no->chave;
        }
        else{
            if(chave < no->chave){
                return busca(chave, no->esq);
            }else{
                return busca(chave, no->dir);
            }
        }
    }else{
        return '\0';
    }   
}

// 7) Elemento imediatamente anterior a 'chave' (maior chave < 'chave'). '\0' se não existir.
//    Nos testes a chave pode NÃO estar na árvore (teste "7x"); mude se discordar.
// PROPOSTA:
// COMPLEXIDADE: O(h) por descer sempre a altura da árvore e sendo h = N no pior caso
auto anterior(char chave, NoBin* no) -> char {
    char melhor = '\0';
    while (no) {
        if (no->chave < chave) {
            melhor = no->chave;
            no = no->dir;
        } else {
            no = no->esq;
        }
    }
    return melhor;

}

// 8) Elemento imediatamente posterior a 'chave' (menor chave > 'chave'). '\0' se não existir.
// PROPOSTA:
// COMPLEXIDADE: O(h) por descer sempre a altura da árvore e sendo h = N no pior caso
auto posterior(char chave, NoBin* no) -> char {
    char melhor = '\0';
    while (no) {
        if (no->chave > chave) {
            melhor = no->chave;
            no = no->esq;
        } else {
            no = no->dir;
        }
    }
    return melhor;
}
