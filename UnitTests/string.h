#ifndef VECTORTESTS_H
#define VECTORTESTS_H

#define HEADER
#include "../microshell.c"

void string_base_test_test(){
};



void string_run_all_tests(){
  string_base_test_test();

  assertResults("Vector Tests");
};

#endif
