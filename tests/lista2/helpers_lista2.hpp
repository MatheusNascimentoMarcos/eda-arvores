// Auxiliares dos TESTES da Lista 2 (não é código de resposta).
#pragma once
#include <algorithm>   // só os TESTES usam; a sua resposta continua proibida de usar
#include <cctype>
#include <queue>
#include <vector>
#include "lista2.hpp"
#include "testlib.hpp"

// Convenção de altura: folha = ALTURA_FOLHA, nulo = ALTURA_FOLHA - 1.
constexpr int ALTURA_FOLHA = 0;

// Constrói a árvore a partir de um vetor em ordem de nível; -1 = nulo.
// Para uma árvore COMPLETA (representação sequencial) basta passar os valores.
inline No* arvN(const std::vector<int>& v) {
    if (v.empty() || v[0] == -1) return nullptr;
    No* raiz = new No{v[0], nullptr, nullptr};
    std::queue<No*> fila;
    fila.push(raiz);
    size_t i = 1;
    while (!fila.empty() && i < v.size()) {
        No* n = fila.front(); fila.pop();
        if (i < v.size() && v[i] != -1) { n->esq = new No{v[i], nullptr, nullptr}; fila.push(n->esq); }
        ++i;
        if (i < v.size() && v[i] != -1) { n->dir = new No{v[i], nullptr, nullptr}; fila.push(n->dir); }
        ++i;
    }
    return raiz;
}

inline void liberar(No* n) { if (!n) return; liberar(n->esq); liberar(n->dir); delete n; }

struct ArvN {
    No* raiz;
    explicit ArvN(const std::vector<int>& v) : raiz(arvN(v)) {}
    ~ArvN() { liberar(raiz); }
    ArvN(const ArvN&) = delete;
    ArvN& operator=(const ArvN&) = delete;
};

// Extrai os números inteiros (não negativos) de um texto impresso.
inline std::vector<int> tokens(const std::string& s) {
    std::vector<int> r;
    long cur = 0; bool dentro = false;
    for (char c : s) {
        if (std::isdigit(static_cast<unsigned char>(c))) { cur = cur * 10 + (c - '0'); dentro = true; }
        else { if (dentro) r.push_back(static_cast<int>(cur)); cur = 0; dentro = false; }
    }
    if (dentro) r.push_back(static_cast<int>(cur));
    return r;
}
#define SAIDA_NUM(...) tokens(capturar([&] { __VA_ARGS__; }))

// --- heap ---
inline bool heapMaxValido(const int* h, int n) {
    for (int i = 1; i < n; ++i) if (h[(i - 1) / 2] < h[i]) return false;
    return true;
}
inline std::vector<int> prefixo(const int* h, int n) { return std::vector<int>(h, h + n); }
inline std::vector<int> ordenado(std::vector<int> v) { std::sort(v.begin(), v.end()); return v; }
