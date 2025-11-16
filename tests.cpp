#define HEADER
#include "microshell.c"

#include "UnitTests/Assert.h"
#include "UnitTests/vector.h"
#include "UnitTests/string.h"
#include "UnitTests/unordered_map.h"




int main(){
  Tests::Assert assert;
  Structures::UnitTests::Unordered_map unordered_map;
  Structures::UnitTests::Vector vector;

  assert.assertion("== Vector result ==\n", vector.runAll());
  assert.assertion("== Unordered_map result ==\n", unordered_map.runAll());

  if(assert.results("=== Unit Tests Result ==="));
    return -1;

  printf("all passed\n");
  return 0;
};