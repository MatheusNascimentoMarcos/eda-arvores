# Uso:
#   make p1 | p2 | p3 | p4      -> lista do Igor (Partes I a IV)
#   make q1 | q2 | q3           -> Lista 2 (Questões 1 a 3)
#   make test                   -> roda tudo
#   make p1 ARGS="1c 1d"        -> roda só alguns exercícios (ids entre colchetes na saída)
#   make check-regras           -> procura usos proibidos (header de algoritmos, max/min...)
#   make SAN= p1                -> compila sem sanitizers (padrão: ASan + UBSan)
#   make clean

CXX      ?= g++
SAN      ?= -fsanitize=address,undefined
CXXFLAGS  = -std=c++17 -Wall -Wextra -Wno-unused-parameter -g -O0 $(SAN) -Iinclude
BUILD     = build
TESTES    = p1 p2 p3 p4 q1 q2 q3
HDRS      = $(wildcard include/*.hpp tests/*/*.hpp src/lista2/*.hpp)

.PHONY: $(TESTES) test check-regras clean

$(TESTES): %: $(BUILD)/%
	@echo "=============== $@ ==============="
	@./$(BUILD)/$@ $(ARGS)

test:
	@for t in $(TESTES); do $(MAKE) --no-print-directory $$t || true; echo; done

$(BUILD):
	@mkdir -p $(BUILD)

$(BUILD)/p1: tests/igor/test_parte1.cpp src/igor/parte1_binarias.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/p2: tests/igor/test_parte2.cpp src/igor/parte2_bst.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/p3: tests/igor/test_parte3.cpp src/igor/parte3_avl.cpp src/igor/parte1_binarias.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/p4: tests/igor/test_parte4.cpp src/igor/parte4_heap.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/q1: tests/lista2/test_q01.cpp src/lista2/q03_arvore.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/q2: tests/lista2/test_q02.cpp src/lista2/q02_heap.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@
$(BUILD)/q3: tests/lista2/test_q03.cpp src/lista2/q03_arvore.cpp $(HDRS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

# Avisa sobre o que o professor proibiu (só olha src/, não os testes).
# Lembrete: o operator= em classes/agregados não dá para detectar automaticamente.
check-regras:
	@if grep -rnE '#include *<algorithm>|std::(max|min|sort|reverse|find|fill|copy|count)\b' src; then \
	  echo "ATENCAO: as linhas acima usam algo proibido pelo professor."; \
	else echo "OK: nenhum uso proibido encontrado em src/."; fi

clean:
	rm -rf $(BUILD)
