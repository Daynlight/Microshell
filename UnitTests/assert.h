#ifndef ASSERT_H
#define ASSERT_H

unsigned int all_total = 0;
unsigned int all_passed = 0;

unsigned int total = 0;
unsigned int passed = 0;

#define assertEQ(str, x, y) \
  total++; \
  if(x != y) \
    printf(COLOR("FAILURE: "str" %d == %d\n", "31"), x, y); \
  else \
    passed++; \
  fflush(stdout); 


#define assertResults(str) \
  all_total++; \
  if(passed == total) \
    printf(COLOR("== "str" == \n%d/%d passed\n", "32"), passed, total); \
  else \
    printf(COLOR("== "str" == \n%d/%d passed\n", "34"), passed, total); \
  if(passed == total) \
    all_passed++;
  

#endif