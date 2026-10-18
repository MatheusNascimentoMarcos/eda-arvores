#include "helpers_lista2.hpp"

// Árvores de teste (ordem de nível, -1 = nulo). Diferentes da árvore da Questão 1.
//   A: perfeita   4 / (2: 1,3) / (6: 5,7)
//   B: 1 / (2: #,4) / (3: 5,#)
//   C: 1 -> direita 2 -> direita 3   (lista à direita)
static const std::vector<int> A{4, 2, 6, 1, 3, 5, 7};
static const std::vector<int> B{1, 2, 3, -1, 4, 5, -1};
static const std::vector<int> C{1, -1, 2, -1, 3};

TESTE(t3a, "3a", "somaFolhas") {
    CHECK_EQ(somaFolhas(nullptr), 0);
    { ArvN t(V({5})); CHECK_EQ(somaFolhas(t.raiz), 5); }
    { ArvN t(A);      CHECK_EQ(somaFolhas(t.raiz), 16); }
    { ArvN t(B);      CHECK_EQ(somaFolhas(t.raiz), 9); }
    { ArvN t(C);      CHECK_EQ(somaFolhas(t.raiz), 3); }
}

TESTE(t3b, "3b", "posOrdem (valores separados por espaço)") {
    { ArvN t(A); CHECK_EQ(SAIDA_NUM(posOrdem(t.raiz)), V({1, 3, 2, 5, 7, 6, 4})); }
    { ArvN t(B); CHECK_EQ(SAIDA_NUM(posOrdem(t.raiz)), V({4, 2, 5, 3, 1})); }
    CHECK_EQ(SAIDA_NUM(posOrdem(nullptr)), V({}));
}

TESTE(t3c, "3c", "emOrdem (valores separados por espaço)") {
    { ArvN t(A); CHECK_EQ(SAIDA_NUM(emOrdem(t.raiz)), V({1, 2, 3, 4, 5, 6, 7})); }
    { ArvN t(B); CHECK_EQ(SAIDA_NUM(emOrdem(t.raiz)), V({2, 4, 1, 5, 3})); }
    CHECK_EQ(SAIDA_NUM(emOrdem(nullptr)), V({}));
}

TESTE(t3d, "3d", "preOrdem (valores separados por espaço)") {
    { ArvN t(A); CHECK_EQ(SAIDA_NUM(preOrdem(t.raiz)), V({4, 2, 1, 3, 6, 5, 7})); }
    { ArvN t(B); CHECK_EQ(SAIDA_NUM(preOrdem(t.raiz)), V({1, 2, 4, 3, 5})); }
    CHECK_EQ(SAIDA_NUM(preOrdem(nullptr)), V({}));
}

TESTE(t3e, "3e", "altura (folha = ALTURA_FOLHA, nulo = ALTURA_FOLHA - 1)") {
    CHECK_EQ(altura(nullptr), ALTURA_FOLHA - 1);
    { ArvN t(V({5})); CHECK_EQ(altura(t.raiz), ALTURA_FOLHA); }
    { ArvN t(A);      CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2); }
    { ArvN t(B);
      CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2);
      CHECK_EQ(altura(t.raiz->esq), ALTURA_FOLHA + 1);
      CHECK_EQ(altura(t.raiz->esq->dir), ALTURA_FOLHA); }
    { ArvN t(C);      CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2); }
}

TESTE(t3f, "3f", "fatorBalanceamento = altura(esq) - altura(dir)") {
    CHECK_EQ(fatorBalanceamento(nullptr), 0);
    { ArvN t(A);  CHECK_EQ(fatorBalanceamento(t.raiz), 0); }
    { ArvN t(B);
      CHECK_EQ(fatorBalanceamento(t.raiz), 0);
      CHECK_EQ(fatorBalanceamento(t.raiz->esq), -1);
      CHECK_EQ(fatorBalanceamento(t.raiz->dir), 1); }
    { ArvN t(C);  CHECK_EQ(fatorBalanceamento(t.raiz), -2); }
}

TESTE(t3g, "3g", "emNiveis (valores separados por espaço)") {
    { ArvN t(A); CHECK_EQ(SAIDA_NUM(emNiveis(t.raiz)), V({4, 2, 6, 1, 3, 5, 7})); }
    { ArvN t(B); CHECK_EQ(SAIDA_NUM(emNiveis(t.raiz)), V({1, 2, 3, 4, 5})); }
    { ArvN t(C); CHECK_EQ(SAIDA_NUM(emNiveis(t.raiz)), V({1, 2, 3})); }
    CHECK_EQ(SAIDA_NUM(emNiveis(nullptr)), V({}));
}

TESTE(t3h, "3h", "produtoNos (árvore vazia => 1)") {
    CHECK_EQ(produtoNos(nullptr), 1LL);
    { ArvN t(V({5})); CHECK_EQ(produtoNos(t.raiz), 5LL); }
    { ArvN t(A);      CHECK_EQ(produtoNos(t.raiz), 5040LL); }
    { ArvN t(B);      CHECK_EQ(produtoNos(t.raiz), 120LL); }
    { ArvN t(C);      CHECK_EQ(produtoNos(t.raiz), 6LL); }
}

TESTES_MAIN()
