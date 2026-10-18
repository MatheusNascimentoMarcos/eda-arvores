#include "helpers_igor.hpp"

// BST de referência (ordem de nível): chaves C F H M P T X
static const char* BST = "MFTCHPX";

TESTE(t2, "2", "insere") {
    Arv t("M");
    const char ordem[] = {'F', 'T', 'C', 'H', 'P', 'X'};
    for (char c : ordem) insere(c, t.raiz);
    Arv esperada(BST);
    CHECK(mesmaEstrutura(t.raiz, esperada.raiz));
    CHECK_EQ(emOrdemStr(t.raiz), "CFHMPTX");
}

TESTE(t2b, "2b", "insere (sequência crescente vira lista à direita)") {
    Arv t("M");
    insere('N', t.raiz); insere('O', t.raiz); insere('P', t.raiz);
    Arv esperada("M#N#O#P");
    CHECK(mesmaEstrutura(t.raiz, esperada.raiz));
}

TESTE(t2x, "2x", "insere chave repetida é ignorada (convenção dos testes)") {
    Arv t(BST);
    insere('F', t.raiz); insere('M', t.raiz); insere('X', t.raiz);
    CHECK_EQ(emOrdemStr(t.raiz), "CFHMPTX");
}

TESTE(t3, "3", "maior (vazia => 'A')") {
    CHECK_EQ(maior(nullptr), 'A');
    { Arv t("M");       CHECK_EQ(maior(t.raiz), 'M'); }
    { Arv t(BST);       CHECK_EQ(maior(t.raiz), 'X'); }
    { Arv t("MFTCH");   CHECK_EQ(maior(t.raiz), 'T'); }
    { Arv t("MF#C");    CHECK_EQ(maior(t.raiz), 'M'); }
}

TESTE(t4, "4", "menor (vazia => 'Z')") {
    CHECK_EQ(menor(nullptr), 'Z');
    { Arv t("M");       CHECK_EQ(menor(t.raiz), 'M'); }
    { Arv t(BST);       CHECK_EQ(menor(t.raiz), 'C'); }
    { Arv t("M#T");     CHECK_EQ(menor(t.raiz), 'M'); }
    { Arv t("MFTCH");   CHECK_EQ(menor(t.raiz), 'C'); }
}

TESTE(t5, "5", "ehBinariaBusca") {
    CHECK_EQ(ehBinariaBusca(nullptr), true);
    { Arv t("M");       CHECK_EQ(ehBinariaBusca(t.raiz), true); }
    { Arv t(BST);       CHECK_EQ(ehBinariaBusca(t.raiz), true); }
    { Arv t("MTF");     CHECK_EQ(ehBinariaBusca(t.raiz), false); }   // filhos trocados
    { Arv t("MFTCZ");   CHECK_EQ(ehBinariaBusca(t.raiz), false); }   // Z na subárvore esquerda de M
    { Arv t("MFTCHPB"); CHECK_EQ(ehBinariaBusca(t.raiz), false); }   // B na subárvore direita de M
    { Arv t("MFTCHEX"); CHECK_EQ(ehBinariaBusca(t.raiz), false); }   // E na subárvore direita de M
}

TESTE(t6, "6", "busca (não achou => '\\0')") {
    CHECK_EQ(busca('M', nullptr), '\0');
    { Arv t(BST);
      CHECK_EQ(busca('M', t.raiz), 'M');
      CHECK_EQ(busca('H', t.raiz), 'H');
      CHECK_EQ(busca('X', t.raiz), 'X');
      CHECK_EQ(busca('C', t.raiz), 'C');
      CHECK_EQ(busca('K', t.raiz), '\0');
      CHECK_EQ(busca('Z', t.raiz), '\0'); }
}

TESTE(t7, "7", "anterior (chave presente)") {
    CHECK_EQ(anterior('M', nullptr), '\0');
    { Arv t(BST);
      CHECK_EQ(anterior('M', t.raiz), 'H');
      CHECK_EQ(anterior('H', t.raiz), 'F');
      CHECK_EQ(anterior('F', t.raiz), 'C');
      CHECK_EQ(anterior('C', t.raiz), '\0');
      CHECK_EQ(anterior('P', t.raiz), 'M');
      CHECK_EQ(anterior('T', t.raiz), 'P');
      CHECK_EQ(anterior('X', t.raiz), 'T'); }
}

TESTE(t7x, "7x", "anterior (chave ausente: maior chave menor que ela)") {
    Arv t(BST);
    CHECK_EQ(anterior('G', t.raiz), 'F');
    CHECK_EQ(anterior('N', t.raiz), 'M');
    CHECK_EQ(anterior('B', t.raiz), '\0');
    CHECK_EQ(anterior('Z', t.raiz), 'X');
}

TESTE(t8, "8", "posterior (chave presente)") {
    CHECK_EQ(posterior('M', nullptr), '\0');
    { Arv t(BST);
      CHECK_EQ(posterior('M', t.raiz), 'P');
      CHECK_EQ(posterior('C', t.raiz), 'F');
      CHECK_EQ(posterior('F', t.raiz), 'H');
      CHECK_EQ(posterior('H', t.raiz), 'M');
      CHECK_EQ(posterior('P', t.raiz), 'T');
      CHECK_EQ(posterior('T', t.raiz), 'X');
      CHECK_EQ(posterior('X', t.raiz), '\0'); }
}

TESTE(t8x, "8x", "posterior (chave ausente: menor chave maior que ela)") {
    Arv t(BST);
    CHECK_EQ(posterior('G', t.raiz), 'H');
    CHECK_EQ(posterior('N', t.raiz), 'P');
    CHECK_EQ(posterior('B', t.raiz), 'C');
    CHECK_EQ(posterior('Z', t.raiz), '\0');
}

TESTES_MAIN()
