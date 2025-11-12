#ifndef VECTORTESTS_H
#define VECTORTESTS_H

#define HEADER
#include "../microshell.c"

void vector_base_test_test(){
  struct Vec2{
    int x;
    int y;
  };
  struct vector vec;

  vector_init(&vec, sizeof(struct Vec2));
  struct Vec2 v1 = {2, 1};
  struct Vec2 v2 = {3, 5};

  vector_push(&vec, (char*)&v1);
  vector_push(&vec, (char*)&v2);

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



void vector_run_all_tests(){
  vector_base_test_test();

  assertResults("Vector Tests");
}

#endif
