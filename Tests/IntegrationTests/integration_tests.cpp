#define HEADER
#include "main.c"

#include "Assert.h"

#include "Structures/string.h"


int main(){
  Tests::Assert assert;

  Structures::IntegrationTests::String string_tests;

  assert.assertion("String Tests", string_tests.runAll());


  if(!assert.results("Integration Tests Result"))
    return -1;

  return 0;
};