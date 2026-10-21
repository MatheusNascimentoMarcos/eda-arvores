// Auxiliares dos TESTES da lista do Igor (não é código de resposta).
#pragma once
#include <queue>
#include <string>
#include "igor.hpp"
#include "testlib.hpp"

// Convenção de altura usada nos testes: folha = ALTURA_FOLHA, nulo = ALTURA_FOLHA - 1.
// (Se a sua convenção é folha = 1 e nulo = 0, troque para 1.)
constexpr int ALTURA_FOLHA = 1;

// Constrói a árvore a partir de uma string em ordem de nível; '#' = nulo.
// Ex.: "ABC#D" -> A(B(#,D), C)
inline NoBin* arv(const std::string& s) {
    if (s.empty() || s[0] == '#') return nullptr;
    NoBin* raiz = new NoBin{s[0], nullptr, nullptr};
    std::queue<NoBin*> fila;
    fila.push(raiz);
    size_t i = 1;
    while (!fila.empty() && i < s.size()) {
        NoBin* n = fila.front(); fila.pop();
        if (i < s.size() && s[i] != '#') { n->esq = new NoBin{s[i], nullptr, nullptr}; fila.push(n->esq); }
        ++i;
        if (i < s.size() && s[i] != '#') { n->dir = new NoBin{s[i], nullptr, nullptr}; fila.push(n->dir); }
        ++i;
    }
    return raiz;
}

inline void liberar(NoBin* n) { if (!n) return; liberar(n->esq); liberar(n->dir); delete n; }

// Árvore que se libera sozinha ao sair do escopo.
struct Arv {
    NoBin* raiz;
    explicit Arv(const std::string& s) : raiz(arv(s)) {}
    ~Arv() { liberar(raiz); }
    Arv(const Arv&) = delete;
    Arv& operator=(const Arv&) = delete;
};

// Mantém só as letras maiúsculas da saída impressa (ignora espaços, vírgulas, quebras).
inline std::string chaves(const std::string& s) {
    std::string r;
    for (char c : s) if (c >= 'A' && c <= 'Z') r.push_back(c);
    return r;
}
#define SAIDA(...) chaves(capturar([&] { __VA_ARGS__; }))

inline std::string emOrdemStr(NoBin* n) {
    if (!n) return "";
    return emOrdemStr(n->esq) + std::string(1, n->chave) + emOrdemStr(n->dir);
}

inline bool mesmaEstrutura(NoBin* a, NoBin* b) {
    if (!a || !b) return a == b;
    return a->chave == b->chave && mesmaEstrutura(a->esq, b->esq) && mesmaEstrutura(a->dir, b->dir);
}

// --- heap ---
inline bool heapMaxValido(const int* h, int n) {
    for (int i = 1; i < n; ++i) if (h[(i - 1) / 2] < h[i]) return false;
    return true;
}
inline std::vector<int> prefixo(const int* h, int n) { return std::vector<int>(h, h + n); }
