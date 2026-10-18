#include "helpers_lista2.hpp"

// Vetor de níveis do enunciado: 20, 10, 15, 4, 7, 8, 3, 1, 2

TESTE(q2a, "2a", "removeMax") {
    { int h[16] = {20, 10, 15, 4, 7, 8, 3, 1, 2};
      int r = removeMax(h, 9);
      CHECK_EQ(r, 20);
      CHECK(heapMaxValido(h, 8));
      CHECK_EQ(ordenado(prefixo(h, 8)), V({1, 2, 3, 4, 7, 8, 10, 15})); }
    { int h[16] = {50, 30, 40, 10, 20, 35};
      int r = removeMax(h, 6);
      CHECK_EQ(r, 50);
      CHECK(heapMaxValido(h, 5));
      CHECK_EQ(h[0], 40);
      CHECK_EQ(ordenado(prefixo(h, 5)), V({10, 20, 30, 35, 40})); }
    { int h[16] = {42};
      CHECK_EQ(removeMax(h, 1), 42); }
    { int h[16] = {9, 8};
      CHECK_EQ(removeMax(h, 2), 9);
      CHECK_EQ(h[0], 8); }
}

TESTE(q2b, "2b", "insereHeap") {
    { int h[16] = {20, 10, 15, 4, 7, 8, 3, 1, 2};
      insereHeap(16, h, 9);
      CHECK(heapMaxValido(h, 10));
      CHECK_EQ(h[0], 20);
      CHECK_EQ(ordenado(prefixo(h, 10)), V({1, 2, 3, 4, 7, 8, 10, 15, 16, 20})); }
    { int h[16] = {20, 10, 15, 4, 7, 8, 3, 1, 2};
      insereHeap(99, h, 9);
      CHECK(heapMaxValido(h, 10));
      CHECK_EQ(h[0], 99); }
    { int h[16] = {20, 10, 15, 4, 7, 8, 3, 1, 2};
      insereHeap(0, h, 9);
      CHECK_EQ(prefixo(h, 10), V({20, 10, 15, 4, 7, 8, 3, 1, 2, 0})); }
    { int h[16] = {0};
      insereHeap(7, h, 0);
      CHECK_EQ(h[0], 7); }
}

TESTES_MAIN()
