#define HEADER
#include "microshell.c"

unsigned int total = 0;
unsigned int passed = 0;

#define assertEQ(str, x, y) \
  total++; \
  if(x != y) \
    printf(COLOR("FAILURE: "str, "31")); \
  else \
    passed++; \

void vector_add_element_test(){
  struct Vec2{
    int x;
    int y;
  };
  struct vector vec;

  vector_init(&vec, sizeof(struct Vec2));
  struct Vec2 v1 = {2, 1};
  struct Vec2 v2 = {3, 5};

  vector_emplace_back(&vec, (char*)&v1);
  vector_emplace_back(&vec, (char*)&v2);

  struct Vec2 v1_t;
  struct Vec2 v2_t;
  vector_get(&vec, (char*)&v1_t, 0);
  vector_get(&vec, (char*)&v2_t, 1);


  assertEQ("Compare Vec2", v1.x, v1_t.x);
  assertEQ("Compare Vec2", v1.y, v1_t.y);
  assertEQ("Compare Vec2", v2.x, v2_t.x);
  assertEQ("Compare Vec2", v2.y, v2_t.y);


  v1_t.x = 21;
  vector_set(&vec, (char*)&v1_t, 0);


  assertEQ("Compare Vec2", 21, v1_t.x);
  assertEQ("Compare Vec2", v1.y, v1_t.y);


  vector_destroy(&vec);
};

int main(){
  vector_add_element_test();

  
  if(passed == total)
    printf(COLOR("%d/%d passed\n", "32"), passed, total);
  else
    printf(COLOR("%d/%d passed\n", "31"), passed, total);
  return 0;
};