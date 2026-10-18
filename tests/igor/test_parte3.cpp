#include "helpers_igor.hpp"

TESTE(t9, "9", "fator = altura(esq) - altura(dir)") {
    CHECK_EQ(fator(nullptr), 0);
    { Arv t("A");        CHECK_EQ(fator(t.raiz), 0); }
    { Arv t("ABC");      CHECK_EQ(fator(t.raiz), 0); }
    { Arv t("AB#");      CHECK_EQ(fator(t.raiz), 1); }
    { Arv t("A#C");      CHECK_EQ(fator(t.raiz), -1); }
    { Arv t("ABCD");     CHECK_EQ(fator(t.raiz), 1); }
    { Arv t("ABCDE#F");  CHECK_EQ(fator(t.raiz), 0); }
    { Arv t("AB#C");
      CHECK_EQ(fator(t.raiz), 2);
      CHECK_EQ(fator(t.raiz->esq), 1);
      CHECK_EQ(fator(t.raiz->esq->esq), 0); }
    { Arv t("A#B#C");    CHECK_EQ(fator(t.raiz), -2); }
}

TESTE(t10, "10", "qualRotacao (imprima só LL, RR, LR ou RL)") {
    { Arv t("CB#A");  CHECK_EQ(SAIDA(qualRotacao(t.raiz)), "LL"); }
    { Arv t("A#B#C"); CHECK_EQ(SAIDA(qualRotacao(t.raiz)), "RR"); }
    { Arv t("CA##B"); CHECK_EQ(SAIDA(qualRotacao(t.raiz)), "LR"); }
    { Arv t("A#CB");  CHECK_EQ(SAIDA(qualRotacao(t.raiz)), "RL"); }
}

TESTES_MAIN()
