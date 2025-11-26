#define HEADER
#include "main.c"

#include "Assert.h"

#include "Structures/vector.h"
#include "Structures/string.h"


int main(){
  Tests::Assert assert;

  Structures::UnitTests::Vector vector_tests;
  Structures::UnitTests::String string_tests;

  assert.assertion("Vector Tests", vector_tests.runAll());
  assert.assertion("String Tests", string_tests.runAll());


  if(!assert.results("Unit Tests Result"))
    return -1;

  return 0;
};