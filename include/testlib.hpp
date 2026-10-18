// Mini framework de testes, sem dependências externas. Você NÃO precisa editar.
// Funciona em Windows (MSVC ou MinGW), Linux e macOS.
//
// Modos de execução (argumentos do executável):
//   ./p1                 roda todos, cada teste num processo separado (um crash não derruba os outros)
//   ./p1 1c 1d           roda só os ids indicados (também isolados)
//   ./p1 --run 1c        roda no MESMO processo, sem isolamento -> use para DEPURAR (breakpoints)
//   ./p1 --child 1c      uso interno (processo filho do modo isolado)
#pragma once
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "todo.hpp"

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
  #include <io.h>
  inline int eda_dup(int fd)            { return _dup(fd); }
  inline int eda_dup2(int a, int b)     { return _dup2(a, b); }
  inline int eda_close(int fd)          { return _close(fd); }
  inline int eda_fileno(FILE* f)        { return _fileno(f); }
#else
  #include <signal.h>
  #include <sys/wait.h>
  #include <unistd.h>
  inline int eda_dup(int fd)            { return dup(fd); }
  inline int eda_dup2(int a, int b)     { return dup2(a, b); }
  inline int eda_close(int fd)          { return close(fd); }
  inline int eda_fileno(FILE* f)        { return fileno(f); }
#endif

inline bool g_falhou = false;
inline std::string g_detalhe;   // detalhe do último crash (para mensagem)

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
    int salvo = eda_dup(1);
#ifdef _WIN32
    char dir[MAX_PATH], path[MAX_PATH];
    GetTempPathA(MAX_PATH, dir);
    GetTempFileNameA(dir, "eda", 0, path);
    FILE* tmp = std::fopen(path, "w+b");
#else
    FILE* tmp = std::tmpfile();
#endif
    eda_dup2(eda_fileno(tmp), 1);
    f();
    std::cout.flush(); std::fflush(stdout);
    eda_dup2(salvo, 1); eda_close(salvo);
    std::rewind(tmp);
    std::string out; char buf[256]; size_t n;
    while ((n = std::fread(buf, 1, sizeof buf, tmp)) > 0) out.append(buf, n);
    std::fclose(tmp);
#ifdef _WIN32
    std::remove(path);
#endif
    return out;
}

// ---------- registro ----------
struct Registro { const char* id; const char* desc; void (*fn)(); };
inline std::vector<Registro>& registros() { static std::vector<Registro> r; return r; }
struct Registrador {
    Registrador(const char* id, const char* desc, void (*fn)()) { registros().push_back(Registro{id, desc, fn}); }
};
#define TESTE(fn, id, desc) static void fn(); static Registrador reg_##fn(id, desc, fn); static void fn()

// ---------- execução ----------
enum { RES_OK = 0, RES_FALHOU = 1, RES_PENDENTE = 2, RES_TIMEOUT = 3, RES_CRASH = 4 };

// Roda um teste no processo atual. Devolve RES_OK / RES_FALHOU / RES_PENDENTE.
inline int executarNoProcesso(const Registro& r) {
    g_pendente = false; g_falhou = false;
    r.fn();
    std::cout << std::flush; std::fflush(stdout);
    return g_pendente ? RES_PENDENTE : (g_falhou ? RES_FALHOU : RES_OK);
}

// Roda um teste num processo separado (isolado), com limite de 5 s.
inline int executarIsolado(const Registro& r, const char* /*argv0*/) {
    std::cout << std::flush; std::fflush(stdout);
#ifdef _WIN32
    char exe[MAX_PATH];
    GetModuleFileNameA(nullptr, exe, MAX_PATH);
    std::string cmd = std::string("\"") + exe + "\" --child " + r.id;
    std::vector<char> linha(cmd.begin(), cmd.end());
    linha.push_back('\0');
    STARTUPINFOA si; std::memset(&si, 0, sizeof si); si.cb = sizeof si;
    PROCESS_INFORMATION pi; std::memset(&pi, 0, sizeof pi);
    if (!CreateProcessA(nullptr, linha.data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
        g_detalhe = "não consegui criar o processo filho";
        return RES_CRASH;
    }
    DWORD w = WaitForSingleObject(pi.hProcess, 5000);
    if (w == WAIT_TIMEOUT) {
        TerminateProcess(pi.hProcess, 1);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
        return RES_TIMEOUT;
    }
    DWORD code = 0;
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess); CloseHandle(pi.hThread);
    if (code <= 2) return static_cast<int>(code);
    char hex[32];
    std::snprintf(hex, sizeof hex, "0x%08lX", static_cast<unsigned long>(code));
    g_detalhe = std::string("código de saída ") + hex + " (0xC0000005 = acesso inválido à memória, 0xC00000FD = estouro de pilha)";
    return RES_CRASH;
#else
    pid_t pid = fork();
    if (pid == 0) {
        alarm(5);  // evita loop infinito
        _exit(executarNoProcesso(r));
    }
    int st = 0; waitpid(pid, &st, 0);
    if (WIFSIGNALED(st)) {
        if (WTERMSIG(st) == SIGALRM) return RES_TIMEOUT;
        g_detalhe = std::string("sinal ") + std::to_string(WTERMSIG(st)) + ": " + strsignal(WTERMSIG(st));
        return RES_CRASH;
    }
    return WEXITSTATUS(st);
#endif
}

inline bool querId(const std::vector<std::string>& ids, const char* id) {
    if (ids.empty()) return true;
    for (size_t i = 0; i < ids.size(); ++i) if (ids[i] == id) return true;
    return false;
}

inline int rodarTestes(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // acentos corretos no terminal
#endif
    std::vector<std::string> args(argv + 1, argv + argc);

    if (args.size() == 2 && args[0] == "--child") {   // processo filho do modo isolado
#ifdef _WIN32
        SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_FAILCRITICALERRORS);  // sem janelas de erro
#endif
        for (auto& r : registros()) if (args[1] == r.id) return executarNoProcesso(r);
        return RES_CRASH;
    }

    bool mesmoProcesso = false;
    if (!args.empty() && args[0] == "--run") { mesmoProcesso = true; args.erase(args.begin()); }

    int ok = 0, falhas = 0, pend = 0;
    for (auto& r : registros()) {
        if (!querId(args, r.id)) continue;
        std::cout << "[" << r.id << "] " << r.desc << "\n" << std::flush;
        int cod = mesmoProcesso ? executarNoProcesso(r) : executarIsolado(r, argv[0]);
        switch (cod) {
            case RES_OK:       ++ok;     std::cout << "    -> OK\n"; break;
            case RES_PENDENTE: ++pend;   std::cout << "    -> PENDENTE (ainda tem TODO())\n"; break;
            case RES_FALHOU:   ++falhas; std::cout << "    -> FALHOU\n"; break;
            case RES_TIMEOUT:  ++falhas; std::cout << "    -> TIMEOUT (loop infinito? limite de 5s)\n"; break;
            default:         ++falhas; std::cout << "    -> CRASH (" << g_detalhe << ")\n"; break;
        }
    }
    std::cout << "\nResumo: " << ok << " OK, " << falhas << " falhou, " << pend << " pendente\n";
    return falhas ? 1 : 0;
}
#define TESTES_MAIN() int main(int argc, char** argv) { return rodarTestes(argc, argv); }
