// Declarações da lista do Prof. Igor (Estruturas de Dados I — Árvores).
#pragma once

struct NoBin {
    char chave;
    NoBin* esq;
    NoBin* dir;
};

// Parte I — Árvores binárias
auto estritaBin(NoBin* no) -> bool;     // 1.a
auto emNiveis(NoBin* no) -> void;       // 1.b
auto ehPerfeita(NoBin* no) -> bool;     // 1.c
auto ehCompleta(NoBin* no) -> bool;     // 1.d
auto altura(NoBin* no) -> int;          // 1.e
auto preordem(NoBin* no) -> void;       // 1.f
auto posordem(NoBin* no) -> void;       // 1.g
auto inorder(NoBin* no) -> void;        // 1.h

// Parte II — Árvores binárias de busca
auto insere(char chave, NoBin* no) -> void;     // 2
auto maior(NoBin* no) -> char;                  // 3
auto menor(NoBin* no) -> char;                  // 4
auto ehBinariaBusca(NoBin* no) -> bool;         // 5
auto busca(char chave, NoBin* no) -> char;      // 6
auto anterior(char chave, NoBin* no) -> char;   // 7
auto posterior(char chave, NoBin* no) -> char;  // 8

// Parte III — AVL
auto fator(NoBin* no) -> int;           // 9
auto qualRotacao(NoBin* no) -> void;    // 10

// Parte IV — Filas de prioridade (int[] do enunciado vira int* em C/C++)
auto ehHeap(int* heap, int N) -> bool;                  // 11
auto novo(int elemento, int* heap, int N) -> void;      // 12
