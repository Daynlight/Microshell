#ifndef MAINTESTS_H
#define MAINTESTS_H

#include "tests.h"
#include "vector.h"
#include "string.h"
#include "path.h"



int main(){
  
  struct passed passed = tests_vector_run_all();
  printf("%d/%d\n", passed.passed, passed.all);

  passed = tests_string_run_all();
  printf("%d/%d\n", passed.passed, passed.all);


  passed = tests_path_run_all();
  printf("%d/%d\n", passed.passed, passed.all);

  return 0;
};



#endif