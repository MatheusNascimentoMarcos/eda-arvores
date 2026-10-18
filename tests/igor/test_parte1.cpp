#include "helpers_igor.hpp"

TESTE(t1a, "1a", "estritaBin") {
    CHECK_EQ(estritaBin(nullptr), true);
    { Arv t("A");       CHECK_EQ(estritaBin(t.raiz), true); }
    { Arv t("ABC");     CHECK_EQ(estritaBin(t.raiz), true); }
    { Arv t("ABCDE");   CHECK_EQ(estritaBin(t.raiz), true); }
    { Arv t("AB#");     CHECK_EQ(estritaBin(t.raiz), false); }
    { Arv t("A#C");     CHECK_EQ(estritaBin(t.raiz), false); }
    { Arv t("ABCD");    CHECK_EQ(estritaBin(t.raiz), false); }
    { Arv t("ABCDEF#"); CHECK_EQ(estritaBin(t.raiz), false); }  // violação só mais embaixo
}

TESTE(t1b, "1b", "emNiveis (imprima só as chaves)") {
    emNiveis(nullptr);
    { Arv t("A");       CHECK_EQ(SAIDA(emNiveis(t.raiz)), "A"); }
    { Arv t("ABC#DE#"); CHECK_EQ(SAIDA(emNiveis(t.raiz)), "ABCDE"); }
    { Arv t("ABCDEFG"); CHECK_EQ(SAIDA(emNiveis(t.raiz)), "ABCDEFG"); }
    { Arv t("A#B#C");   CHECK_EQ(SAIDA(emNiveis(t.raiz)), "ABC"); }
    { Arv t("ABCD#EF"); CHECK_EQ(SAIDA(emNiveis(t.raiz)), "ABCDEF"); }
    CHECK_EQ(SAIDA(emNiveis(nullptr)), "");
}

TESTE(t1c, "1c", "ehPerfeita") {
    CHECK_EQ(ehPerfeita(nullptr), true);
    { Arv t("A");       CHECK_EQ(ehPerfeita(t.raiz), true); }
    { Arv t("ABC");     CHECK_EQ(ehPerfeita(t.raiz), true); }
    { Arv t("ABCDEFG"); CHECK_EQ(ehPerfeita(t.raiz), true); }
    { Arv t("AB#");     CHECK_EQ(ehPerfeita(t.raiz), false); }
    { Arv t("ABCD");    CHECK_EQ(ehPerfeita(t.raiz), false); }
    { Arv t("ABCDEF");  CHECK_EQ(ehPerfeita(t.raiz), false); }
    { Arv t("ABC#D");   CHECK_EQ(ehPerfeita(t.raiz), false); }
    { Arv t("ABCDE");   CHECK_EQ(ehPerfeita(t.raiz), false); }  // estrita, mas folhas em níveis diferentes
}

TESTE(t1d, "1d", "ehCompleta") {
    CHECK_EQ(ehCompleta(nullptr), true);
    { Arv t("A");       CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("ABC");     CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("AB#");     CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("ABCD");    CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("ABCDE");   CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("ABCDEF");  CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("ABCDEFG"); CHECK_EQ(ehCompleta(t.raiz), true); }
    { Arv t("A#C");     CHECK_EQ(ehCompleta(t.raiz), false); }
    { Arv t("ABC#D");   CHECK_EQ(ehCompleta(t.raiz), false); }
    { Arv t("ABCDE#G"); CHECK_EQ(ehCompleta(t.raiz), false); }
    { Arv t("ABCD#EF"); CHECK_EQ(ehCompleta(t.raiz), false); }
}

TESTE(t1e, "1e", "altura (folha = ALTURA_FOLHA, nulo = ALTURA_FOLHA - 1)") {
    CHECK_EQ(altura(nullptr), ALTURA_FOLHA - 1);
    { Arv t("A");       CHECK_EQ(altura(t.raiz), ALTURA_FOLHA); }
    { Arv t("ABC");     CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 1); }
    { Arv t("ABCDEFG"); CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2); }
    { Arv t("ABC#D");
      CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2);
      CHECK_EQ(altura(t.raiz->esq), ALTURA_FOLHA + 1);
      CHECK_EQ(altura(t.raiz->dir), ALTURA_FOLHA); }
    { Arv t("A#B#C");   CHECK_EQ(altura(t.raiz), ALTURA_FOLHA + 2); }
}

TESTE(t1f, "1f", "preordem (imprima só as chaves)") {
    { Arv t("FBGAD#I"); CHECK_EQ(SAIDA(preordem(t.raiz)), "FBADGI"); }
    { Arv t("ABC#DE#"); CHECK_EQ(SAIDA(preordem(t.raiz)), "ABDCE"); }
    { Arv t("A");       CHECK_EQ(SAIDA(preordem(t.raiz)), "A"); }
    CHECK_EQ(SAIDA(preordem(nullptr)), "");
}

TESTE(t1g, "1g", "posordem (imprima só as chaves)") {
    { Arv t("FBGAD#I"); CHECK_EQ(SAIDA(posordem(t.raiz)), "ADBIGF"); }
    { Arv t("ABC#DE#"); CHECK_EQ(SAIDA(posordem(t.raiz)), "DBECA"); }
    { Arv t("A");       CHECK_EQ(SAIDA(posordem(t.raiz)), "A"); }
    CHECK_EQ(SAIDA(posordem(nullptr)), "");
}

TESTE(t1h, "1h", "inorder (imprima só as chaves)") {
    { Arv t("FBGAD#I"); CHECK_EQ(SAIDA(inorder(t.raiz)), "ABDFGI"); }
    { Arv t("ABC#DE#"); CHECK_EQ(SAIDA(inorder(t.raiz)), "BDAEC"); }
    { Arv t("A");       CHECK_EQ(SAIDA(inorder(t.raiz)), "A"); }
    CHECK_EQ(SAIDA(inorder(nullptr)), "");
}

TESTES_MAIN()
