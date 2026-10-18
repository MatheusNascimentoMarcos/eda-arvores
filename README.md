# eda-arvores — listas de Árvores (Estruturas de Dados I)

Repositório para **você escrever e testar** as respostas das duas listas:

- **Lista do Prof. Igor** (Árvores: binárias, BST, AVL, heap) — exercícios 1.a–1.h, 2–12
- **Lista 2 – EDA** — questões 1, 2 e 3

Os arquivos em `src/` já vêm com as funções declaradas, o enunciado em comentário e um `TODO()`.
Os testes em `tests/` dizem se cada exercício está certo. **Nenhuma resposta está pronta.**

## Estrutura

```
eda-arvores/
├── CMakeLists.txt          build + testes via CMake/CTest (Windows, Linux, macOS)
├── Makefile                build + testes via make (Linux, macOS, WSL)
├── .vscode/settings.json   configuração do CMake Tools (pasta de build, args do debug)
├── include/
│   ├── igor.hpp            struct NoBin + assinaturas da lista do Igor
│   ├── lista2.hpp          class No / Arvore + assinaturas da Lista 2
│   ├── todo.hpp            macro TODO() (marca "ainda não feito")
│   └── testlib.hpp         mini framework de testes (não editar)
├── src/                    >>> SEU CÓDIGO FICA AQUI <<<
│   ├── igor/
│   │   ├── parte1_binarias.cpp   1.a–1.h
│   │   ├── parte2_bst.cpp        2–8
│   │   ├── parte3_avl.cpp        9–10
│   │   └── parte4_heap.cpp       11–12
│   └── lista2/
│       ├── q01_respostas.hpp     Q1 (à mão): digite aqui suas respostas
│       ├── q02_heap.cpp          Q2: removeMax / insereHeap
│       └── q03_arvore.cpp        Q3(a–h)
├── tests/                  testes (igor/ e lista2/)
└── docs/
    ├── igor_discussao.md             proposta + complexidade de cada exercício
    └── lista2_q02_passo_a_passo.md   desenhos da Q2 (árvore e vetor)
```

## Alvos de teste

| Alvo | Conteúdo | Exercícios (ids) |
|---|---|---|
| `p1` | Igor, Parte I (binárias) | 1a 1b 1c 1d 1e 1f 1g 1h |
| `p2` | Igor, Parte II (BST) | 2 2b 2x 3 4 5 6 7 7x 8 8x |
| `p3` | Igor, Parte III (AVL) | 9 10 |
| `p4` | Igor, Parte IV (heap) | 11 12 |
| `q1` | Lista 2, Q1 (confere sua resposta manual com o seu código) | 1a 1b 1c |
| `q2` | Lista 2, Q2 (heap) | 2a 2b |
| `q3` | Lista 2, Q3 (árvore) | 3a 3b 3c 3d 3e 3f 3g 3h |

O resultado de cada exercício é `OK`, `FALHOU` (com obtido x esperado), `PENDENTE` (ainda tem `TODO()`),
`CRASH` (segfault etc.) ou `TIMEOUT` (loop infinito, limite de 5 s). Um exercício quebrado não derruba os outros.

**Fluxo:** abra o arquivo de `src/` → escreva a proposta e a complexidade nos comentários →
implemente → **apague o `TODO();`** → compile e rode o alvo.

## Opção A — CMake (Windows nativo, Linux, macOS)

Não precisa de WSL. Instale uma vez:

1. **CMake** (`winget install Kitware.CMake` no Windows).
2. Um **compilador C++17**: no Windows, o *Build Tools for Visual Studio* (carga "Desenvolvimento para desktop com C++")
   ou o MSYS2/MinGW-w64; em Linux/macOS, `g++` ou `clang++`.

Linha de comando:

```bash
cmake -S . -B build-cmake                    # configura (uma vez)
cmake --build build-cmake --target p1        # SÓ compila o alvo p1 (não roda nada)
cmake --build build-cmake                    # compila todos os alvos
```

Rodar **depois**, isoladamente. O executável fica em `build-cmake/p1` (Ninja/MinGW/Linux/macOS) ou
`build-cmake/Debug/p1.exe` (gerador do Visual Studio):

```bash
./build-cmake/p1                  # todos os exercícios da parte
./build-cmake/p1 1c 1d            # só 1.c e 1.d (cada um num processo isolado)
```

Ou pelo CTest, que tem um teste por exercício (`p1.1c`, `p2.7x`, `q3.3e`...):

```bash
ctest --test-dir build-cmake -C Debug --output-on-failure                  # tudo
ctest --test-dir build-cmake -C Debug -R "^p1\." --output-on-failure       # uma parte
ctest --test-dir build-cmake -C Debug -R "^p1\.1c$" --output-on-failure    # um exercício
```

No CTest, exercício `PENDENTE` conta como falho (é um lembrete do que falta).
Para compilar sem sanitizers: `-DSANITIZERS=OFF` (eles já vêm desligados no Windows).

### No VS Code

1. Instale as extensões **C/C++** e **CMake Tools** (Microsoft).
2. **Ctrl+Shift+P → CMake: Select a Kit** e escolha o compilador.
3. Na barra de status, escolha o **alvo** (`p1`…`q3`) e clique em **Build** (só compila).
4. Painel **Testing** (frasco): rode um exercício, uma parte ou tudo; o botão de debug também funciona ali.
5. Debug pela barra de status: troque o id em `.vscode/settings.json` (`"args": ["--run", "1c"]`) e aperte o bug.

O modo `--run <id>` roda no **mesmo processo**, sem isolamento — é ele que permite o depurador parar nos
seus breakpoints. Use `./build-cmake/p1 --run 1c` também no terminal se quiser rodar sem criar processo filho.

## Opção B — Makefile (Linux, macOS, WSL)

```bash
make p1 | p2 | p3 | p4      # compila e roda a parte
make q1 | q2 | q3
make test                   # tudo de uma vez
make p1 ARGS="1c 1d"        # só alguns exercícios
make build/p1               # SÓ compila (depois: ./build/p1 1c)
make build-all              # compila todos, sem rodar (veja nota abaixo)
make check-regras           # procura <algorithm>, std::max/min/sort... em src/
make SAN= p1                # sem sanitizers (padrão: ASan + UBSan)
make clean
```

> `make build-all` só existe se você adicionar ao `Makefile`:
> `.PHONY: build-all` e `build-all: $(TESTES:%=$(BUILD)/%)`.

O `make` não existe no PowerShell/Windows nativo: use a Opção A (ou o WSL).

## Regras do professor (valem para tudo em `src/`)

- Sem `<algorithm>` — **inclui `std::max`, `std::min`, `std::sort`...** (escreva um `if`).
- Sem `operator=` em classes/agregados: use `=` só com tipos primitivos e ponteiros.
  (`std::queue`, `std::vector` etc. podem ser usados, mas não copie/atribua um contêiner a outro.)
- Discuta a proposta e analise a complexidade de **cada** método (comentários `PROPOSTA:` /
  `COMPLEXIDADE:` ou `docs/igor_discussao.md`).
- Os testes em `tests/` não seguem essas regras (só os arquivos de `src/` precisam seguir).
- `make check-regras` (ou `grep -rn "algorithm\|std::max\|std::min" src`) ajuda a conferir;
  o uso indevido de `operator=` não dá para detectar automaticamente.

## Convenções assumidas pelos testes

Os enunciados deixam alguns pontos em aberto. Eu fixei estas convenções; se a sua turma usa outra, edite o
teste (`tests/...`) e/ou a constante indicada.

| Tema | Convenção |
|---|---|
| Assinaturas | `int[] heap` do enunciado vira `int* heap`. |
| Altura | folha = 0, nó nulo = -1 (`ALTURA_FOLHA` em `tests/*/helpers_*.hpp`; troque para 1 se folha = 1). |
| Fator de balanceamento | `altura(esq) - altura(dir)`; nó nulo → 0. |
| Impressões (Igor) | imprima **só as chaves** (espaços/quebras de linha são ignorados). |
| Impressões (Lista 2) | números separados por espaço. |
| `qualRotacao` | imprime exatamente `LL`, `RR`, `LR` ou `RL` (LL = simples à direita, RR = simples à esquerda). |
| Heap | **max-heap**, índices a partir de 0, `N` = quantidade atual de elementos. |
| `insere` na BST | a raiz já existe; chave repetida é ignorada (teste `2x`). |
| `anterior` / `posterior` | maior chave `<` / menor chave `>` a `chave`; `'\0'` se não existir. A chave pode estar ausente (testes `7x`/`8x`). |
| `maior` / `menor` | árvore vazia → `'A'` / `'Z'`, como no enunciado. |
| Lista 2, Q3 | funções recebem `No*` (use `arvore.raiz` para a árvore toda); produto da árvore vazia = 1. |

## Dicas

- Comece pelos percursos e pela altura (1.e–1.h): quase tudo depende deles.
- Para depurar só um exercício: `./build-cmake/p1 --run 1d` (ou `make p1 ARGS="1d"`). Pode usar `printf` à vontade (apague depois).
- Questão 1 da Lista 2: resolva no papel, digite em `src/lista2/q01_respostas.hpp` e rode `q1`
  depois de implementar a Q3(b–d).
- Questão 2 da Lista 2: os desenhos passo a passo vão em `docs/lista2_q02_passo_a_passo.md`.
- Se algo falhar ao compilar no Windows, confira se o kit do CMake Tools é um compilador C++17
  e apague a pasta `build-cmake/` para reconfigurar do zero.
- Faça commits pequenos, um por exercício (`git add . && git commit -m "1.a estritaBin" && git push`).
  A pasta `build/` e a `build-cmake/` não devem ir para o Git (veja o `.gitignore`).
