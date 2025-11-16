#define HEADER
#include "../microshell.c"

#include "Assert.h"

#include "vector.h"
#include "unordered_map.h"
#include "string.h"




int main(){
  Tests::Assert assert;
  Structures::UnitTests::Unordered_map unordered_map;
  Structures::UnitTests::Vector vector;

  assert.assertion("== Vector result ==\n", vector.runAll());
  assert.assertion("== Unordered_map result ==\n", unordered_map.runAll());

  if(!assert.results("Unit Tests Result"))
    return -1;

  return 0;
};