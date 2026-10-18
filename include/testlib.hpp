// Mini framework de testes, sem dependências externas. Você NÃO precisa editar.
// Cada teste roda em um processo separado (fork): se um exercício der
// segfault ou loop infinito, os outros testes continuam rodando.
// Requer Linux / macOS / WSL.
#pragma once
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "todo.hpp"

inline bool g_falhou = false;

// ---------- impressão de valores nas mensagens de erro ----------
template <class T> void mostrar(const T& v) { std::cout << v; }
inline void mostrar(bool b) { std::cout << (b ? "true" : "false"); }
inline void mostrar(char c) {
    if (c == '\0') std::cout << "'\\0'"; else std::cout << "'" << c << "'";
}
inline void mostrar(const std::string& s) { std::cout << "\"" << s << "\""; }
inline void mostrar(const std::vector<int>& v) {
    std::cout << "{";
    for (size_t i = 0; i < v.size(); ++i) std::cout << (i ? ", " : "") << v[i];
    std::cout << "}";
}

#define CHECK(cond) do { if (!(cond)) { g_falhou = true; \
    std::cout << "        falhou (linha " << __LINE__ << "): " << #cond << "\n"; } } while (0)

#define CHECK_EQ(obtido, esperado) do { auto _o = (obtido); auto _e = (esperado); \
    if (!(_o == _e)) { g_falhou = true; \
        std::cout << "        falhou (linha " << __LINE__ << "): " << #obtido << "\n          obtido:   "; \
        mostrar(_o); std::cout << "\n          esperado: "; mostrar(_e); std::cout << "\n"; } } while (0)

// V({1,2,3}) -> std::vector<int>  (útil dentro de CHECK_EQ por causa das vírgulas)
inline std::vector<int> V(std::initializer_list<int> l) { return std::vector<int>(l); }

// ---------- captura do stdout (funciona com printf E com std::cout) ----------
template <class F> std::string capturar(F f) {
    std::cout.flush(); std::fflush(stdout);
    int salvo = dup(1);
    FILE* tmp = std::tmpfile();
    dup2(fileno(tmp), 1);
    f();
    std::cout.flush(); std::fflush(stdout);
    dup2(salvo, 1); close(salvo);
    std::rewind(tmp);
    std::string out; char buf[256]; size_t n;
    while ((n = std::fread(buf, 1, sizeof buf, tmp)) > 0) out.append(buf, n);
    std::fclose(tmp);
    return out;
}

// ---------- registro e execução ----------
struct Registro { const char* id; const char* desc; void (*fn)(); };
inline std::vector<Registro>& registros() { static std::vector<Registro> r; return r; }
struct Registrador {
    Registrador(const char* id, const char* desc, void (*fn)()) { registros().push_back(Registro{id, desc, fn}); }
};
#define TESTE(fn, id, desc) static void fn(); static Registrador reg_##fn(id, desc, fn); static void fn()

inline int rodarTestes(int argc, char** argv) {
    int ok = 0, falhas = 0, pend = 0;
    for (auto& r : registros()) {
        if (argc > 1) {  // filtro: ./build/p1 1a 1c
            bool quer = false;
            for (int i = 1; i < argc; ++i) if (std::string(argv[i]) == r.id) quer = true;
            if (!quer) continue;
        }
        std::cout << "[" << r.id << "] " << r.desc << "\n" << std::flush;
        pid_t pid = fork();
        if (pid == 0) {
            alarm(5);  // evita loop infinito
            g_pendente = false; g_falhou = false;
            r.fn();
            std::cout << std::flush; std::fflush(stdout);
            _exit(g_pendente ? 2 : (g_falhou ? 1 : 0));
        }
        int st = 0; waitpid(pid, &st, 0);
        if (WIFSIGNALED(st)) {
            ++falhas;
            if (WTERMSIG(st) == SIGALRM) std::cout << "    -> TIMEOUT (loop infinito? limite de 5s)\n";
            else std::cout << "    -> CRASH (sinal " << WTERMSIG(st) << ": " << strsignal(WTERMSIG(st)) << ")\n";
        } else if (WEXITSTATUS(st) == 0) { ++ok;    std::cout << "    -> OK\n"; }
        else if (WEXITSTATUS(st) == 2)   { ++pend;  std::cout << "    -> PENDENTE (ainda tem TODO())\n"; }
        else                             { ++falhas; std::cout << "    -> FALHOU\n"; }
    }
    std::cout << "\nResumo: " << ok << " OK, " << falhas << " falhou, " << pend << " pendente\n";
    return falhas ? 1 : 0;
}
#define TESTES_MAIN() int main(int argc, char** argv) { return rodarTestes(argc, argv); }
