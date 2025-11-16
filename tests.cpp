#include "UnitTests/assert.h"
#include "UnitTests/vector.h"
#include "UnitTests/string.h"
#include "UnitTests/unordered_map.h"




int main(){
  vector_run_all_tests();

  printf(COLOR("==== All Tests ====\n", "32"));
  if(all_passed == all_total)
    printf(COLOR("%d/%d passed\n", "32"), all_passed, all_total);
  else
    printf(COLOR("%d/%d passed\n", "34"), all_passed, all_total);
  
  if(all_passed != all_total)
    return -1;

  return 0;
};