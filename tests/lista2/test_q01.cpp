// Confere a Questão 1 (feita à mão) usando os SEUS percursos de q03_arvore.cpp.
#include "helpers_lista2.hpp"
#include "../../src/lista2/q01_respostas.hpp"

TESTE(q1a, "1a", "pré-ordem: sua resposta manual x seu código") {
    if (RESP_PRE.empty()) { TODO(); return; }
    ArvN t(ENTRADA);
    std::vector<int> obtido = SAIDA_NUM(preOrdem(t.raiz));
    CHECK_EQ(obtido, RESP_PRE);
}

TESTE(q1b, "1b", "em-ordem: sua resposta manual x seu código") {
    if (RESP_IN.empty()) { TODO(); return; }
    ArvN t(ENTRADA);
    std::vector<int> obtido = SAIDA_NUM(emOrdem(t.raiz));
    CHECK_EQ(obtido, RESP_IN);
}

TESTE(q1c, "1c", "pós-ordem: sua resposta manual x seu código") {
    if (RESP_POS.empty()) { TODO(); return; }
    ArvN t(ENTRADA);
    std::vector<int> obtido = SAIDA_NUM(posOrdem(t.raiz));
    CHECK_EQ(obtido, RESP_POS);
}

TESTES_MAIN()
