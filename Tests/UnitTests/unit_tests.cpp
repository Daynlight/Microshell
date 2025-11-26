#define HEADER
#include "main.c"

#include "Assert.h"

#include "Vector/vector.h"


int main(){
  Tests::Assert assert;

  Structures::UnitTests::Vector vector_tests;

  assert.assertion("Vector Tests", vector_tests.runAll());


  if(!assert.results("Unit Tests Result"))
    return -1;

  return 0;
};