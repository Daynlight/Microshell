#define HEADER
#include "../microshell.c"

#include "Assert.h"



int main(){
  Tests::Assert assert;

  if(!assert.results("Unit Tests Result"))
    return -1;

  return 0;
};