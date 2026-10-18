cmake_minimum_required(VERSION 3.16)
project(eda_arvores CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug)   # -g -O0
endif()

# ASan/UBSan: úteis em Linux/macOS; desligados por padrão no Windows.
if(WIN32)
  option(SANITIZERS "Compilar com AddressSanitizer + UBSan" OFF)
else()
  option(SANITIZERS "Compilar com AddressSanitizer + UBSan" ON)
endif()

enable_testing()

# add_teste(<alvo> <fontes...>) -> executável de testes
function(add_teste nome)
  add_executable(${nome} ${ARGN})
  target_include_directories(${nome} PRIVATE include)
  if(MSVC)
    target_compile_options(${nome} PRIVATE /W4 /utf-8 /wd4100)
    target_compile_definitions(${nome} PRIVATE _CRT_SECURE_NO_WARNINGS)
  else()
    target_compile_options(${nome} PRIVATE -Wall -Wextra -Wno-unused-parameter)
    if(SANITIZERS)
      target_compile_options(${nome} PRIVATE -fsanitize=address,undefined)
      target_link_options(${nome} PRIVATE -fsanitize=address,undefined)
    endif()
  endif()
endfunction()

# add_exercicios(<alvo> <ids...>) -> um teste do CTest por exercício.
# Usa "--run" (mesmo processo): o CTest já isola cada teste e dá timeout,
# e assim o depurador do VS Code consegue parar nos seus breakpoints.
# Falha no CTest: FALHOU, CRASH, TIMEOUT e também PENDENTE (ainda não feito).
function(add_exercicios nome)
  foreach(id ${ARGN})
    add_test(NAME ${nome}.${id} COMMAND ${nome} --run ${id})
    set_tests_properties(${nome}.${id} PROPERTIES
      TIMEOUT 10
      FAIL_REGULAR_EXPRESSION "-> (FALHOU|PENDENTE|CRASH|TIMEOUT)")
  endforeach()
endfunction()

# ---------------- Lista do Prof. Igor ----------------
add_teste(p1 tests/igor/test_parte1.cpp src/igor/parte1_binarias.cpp)
add_exercicios(p1 1a 1b 1c 1d 1e 1f 1g 1h)

add_teste(p2 tests/igor/test_parte2.cpp src/igor/parte2_bst.cpp)
add_exercicios(p2 2 2b 2x 3 4 5 6 7 7x 8 8x)

# p3 também linka a Parte I: fator() pode reaproveitar altura()
add_teste(p3 tests/igor/test_parte3.cpp src/igor/parte3_avl.cpp src/igor/parte1_binarias.cpp)
add_exercicios(p3 9 10)

add_teste(p4 tests/igor/test_parte4.cpp src/igor/parte4_heap.cpp)
add_exercicios(p4 11 12)

# ---------------- Lista 2 ----------------
add_teste(q1 tests/lista2/test_q01.cpp src/lista2/q03_arvore.cpp)
add_exercicios(q1 1a 1b 1c)

add_teste(q2 tests/lista2/test_q02.cpp src/lista2/q02_heap.cpp)
add_exercicios(q2 2a 2b)

add_teste(q3 tests/lista2/test_q03.cpp src/lista2/q03_arvore.cpp)
add_exercicios(q3 3a 3b 3c 3d 3e 3f 3g 3h)
