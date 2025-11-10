#define HEADER
#include "microshell.c"

unsigned int total = 0;
unsigned int passed = 0;

#define assertEQ(str, x, y) \
  total++; \
  if(x != y) \
    printf(COLOR("FAILURE: "str" %d == %d\n", "31"), x, y); \
  else \
    passed++; \




void vector_test(){
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


  assertEQ("Vector: Compare Vec2", v1.x, v1_t.x);
  assertEQ("Vector: Compare Vec2", v1.y, v1_t.y);
  assertEQ("Vector: Compare Vec2", v2.x, v2_t.x);
  assertEQ("Vector: Compare Vec2", v2.y, v2_t.y);


  v1.x = 21;
  vector_set(&vec, (char*)&v1, 0);
  vector_get(&vec, (char*)&v1_t, 0);


  assertEQ("Vector: Compare Vec2", v1.x, v1_t.x);
  assertEQ("Vector: Compare Vec2", v1.y, v1_t.y);


  vector_destroy(&vec);
};




void unordered_map_test(){
  struct Vec2{
    int x;
    int y;
  };
  struct unordered_map map;

  unordered_map_init(&map);
  
  char v1_name[] = "vec1";
  char v2_name[] = "vec2";

  struct Vec2 v1 = {2, 1};
  struct Vec2 v2 = {3, 5};

  unordered_map_set(&map, (char*)&v1, v1_name);
  unordered_map_set(&map, (char*)&v2, v2_name);

  struct Vec2 v1_t;
  struct Vec2 v2_t;

  unordered_map_get(&map, (char*)&v1_t, v1_name);
  unordered_map_get(&map, (char*)&v2_t, v2_name);


  assertEQ("Unordered_map: Compare Vec2", v1.x, v1_t.x);
  assertEQ("Unordered_map: Compare Vec2", v1.y, v1_t.y);
  assertEQ("Unordered_map: Compare Vec2", v2.x, v2_t.x);
  assertEQ("Unordered_map: Compare Vec2", v2.y, v2_t.y);


  v1.x = 21;
  unordered_map_set(&map, (char*)&v1, v1_name);
  unordered_map_get(&map, (char*)&v1_t, v1_name);

  assertEQ("Unordered_map: Compare Vec2", v1.x, v1_t.x);
  assertEQ("Unordered_map: Compare Vec2", v1.y, v1_t.y);


  unordered_map_destroy(&map);
};









int main(){
  vector_test();
  unordered_map_test();

  
  if(passed == total)
    printf(COLOR("%d/%d passed\n", "32"), passed, total);
  else
    printf(COLOR("%d/%d passed\n", "34"), passed, total);
  
  if(passed != total)
    return -1;
    
  return 0;
};