# eda-arvores — listas de Árvores (Estruturas de Dados I)

Repositório para **você escrever e testar** as respostas das duas listas:

- **Lista do Prof. Igor** (Árvores: binárias, BST, AVL, heap) — exercícios 1.a–1.h, 2–12
- **Lista 2 – EDA** — questões 1, 2 e 3

Os arquivos em `src/` já vêm com as funções declaradas, o enunciado em comentário e um `TODO()`.
Os testes em `tests/` dizem se cada exercício está certo. **Nenhuma resposta está pronta.**

## Estrutura

```
eda-arvores/
├── Makefile
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

## Como usar

Requer `g++` (C++17) e `make`, em Linux, macOS ou WSL.

```bash
make p1            # Igor, Parte I      (1.a–1.h)
make p2            # Igor, Parte II     (2–8)
make p3            # Igor, Parte III    (9–10)
make p4            # Igor, Parte IV     (11–12)
make q1            # Lista 2, Q1 (confere sua resposta manual com o seu código)
make q2            # Lista 2, Q2
make q3            # Lista 2, Q3
make test          # tudo de uma vez
make p1 ARGS="1c 1d"     # só alguns exercícios (o id aparece entre [colchetes])
make check-regras        # procura <algorithm>, std::max/min/sort... em src/
```

Cada exercício aparece como `OK`, `FALHOU` (com obtido x esperado), `PENDENTE` (ainda tem `TODO()`),
`CRASH` (segfault) ou `TIMEOUT` (loop infinito, limite de 5 s). Um exercício quebrado não derruba os outros.
Por padrão compila com AddressSanitizer + UBSan (acusa acesso inválido à memória); `make SAN= p1` desliga.

**Fluxo:** abra o arquivo de `src/` → escreva a proposta e a complexidade nos comentários →
implemente → **apague o `TODO();`** → `make pX`.

## Regras do professor (valem para tudo em `src/`)

- Sem `<algorithm>` — **inclui `std::max`, `std::min`, `std::sort`...** (escreva um `if`).
- Sem `operator=` em classes/agregados: use `=` só com tipos primitivos e ponteiros.
  (`std::queue`, `std::vector` etc. podem ser usados, mas não copie/atribua um contêiner a outro.)
- Discuta a proposta e analise a complexidade de **cada** método (comentários `PROPOSTA:` /
  `COMPLEXIDADE:` ou `docs/igor_discussao.md`).
- Os testes em `tests/` não seguem essas regras (só os arquivos de `src/` precisam seguir).

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
- Para depurar, rode só o exercício: `make p1 ARGS="1d"`. Pode usar `printf` à vontade (apague depois).
- Questão 1 da Lista 2: resolva no papel, digite em `src/lista2/q01_respostas.hpp` e rode `make q1`
  depois de implementar a Q3(b–d).
- `git init && git add . && git commit -m "esqueleto"` antes de começar ajuda a acompanhar seu progresso.
