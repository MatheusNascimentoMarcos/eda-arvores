#include "helpers_igor.hpp"

TESTE(t11, "11", "ehHeap (max-heap, índices a partir de 0)") {
    { int h[] = {20, 10, 15, 4, 7, 8, 3, 1, 2};  CHECK_EQ(ehHeap(h, 9), true); }
    { int h[] = {5};                             CHECK_EQ(ehHeap(h, 1), true); }
    { int h[] = {1};                             CHECK_EQ(ehHeap(h, 0), true); }
    { int h[] = {10, 20};                        CHECK_EQ(ehHeap(h, 2), false); }
    { int h[] = {20, 10, 15, 4, 7, 8, 3, 1, 25}; CHECK_EQ(ehHeap(h, 9), false); }
    { int h[] = {20, 10, 15, 4, 7, 8, 3, 1, 25}; CHECK_EQ(ehHeap(h, 8), true); }  // só os N primeiros contam
    { int h[] = {9, 9, 9, 9};                    CHECK_EQ(ehHeap(h, 4), true); }  // iguais valem
}

TESTE(t12, "12", "novo (insere no heap)") {
    { int h[16] = {50, 30, 40, 10, 20};
      novo(45, h, 5);  CHECK_EQ(prefixo(h, 6), V({50, 30, 45, 10, 20, 40})); }
    { int h[16] = {50, 30, 40, 10, 20};
      novo(60, h, 5);  CHECK_EQ(prefixo(h, 6), V({60, 30, 50, 10, 20, 40})); }
    { int h[16] = {50, 30, 40, 10, 20};
      novo(5, h, 5);   CHECK_EQ(prefixo(h, 6), V({50, 30, 40, 10, 20, 5})); }
    { int h[16] = {0};
      novo(7, h, 0);   CHECK_EQ(prefixo(h, 1), V({7})); }
    { int h[16] = {0}; int n = 0;
      const int xs[] = {3, 9, 1, 7, 5, 8, 2};
      for (int x : xs) { novo(x, h, n); ++n; }
      CHECK(heapMaxValido(h, n));
      CHECK_EQ(h[0], 9); }
}

TESTES_MAIN()
