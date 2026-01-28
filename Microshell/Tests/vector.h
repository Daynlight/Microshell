#ifndef VECTORTESTS_H
#define VECTORTESTS_H

#include <stdio.h>
#include "tests.h"
#include "../Structures/Vector/vector.h"

struct passed tests_vector_run_all();

char tests_vector_init();
char tests_vector_destroy();
char tests_vector_resize();
char tests_vector_reserve();
char tests_vector_fit();
char tests_vector_shrink();
char tests_vector_alloc();
char tests_vector_get();
char tests_vector_set();
char tests_vector_push();
char tests_vector_pop();
char tests_vector_clean();
char tests_vector_erase();
char tests_vector_copy();

struct passed tests_vector_run_all() {
  struct passed passed = {0};

  printf("==== Vector Tests ====\n");

  if (tests_vector_init()) passed.passed++;
  if (tests_vector_destroy()) passed.passed++;
  if (tests_vector_resize()) passed.passed++;
  if (tests_vector_reserve()) passed.passed++;
  if (tests_vector_fit()) passed.passed++;
  if (tests_vector_shrink()) passed.passed++;
  if (tests_vector_alloc()) passed.passed++;
  if (tests_vector_get()) passed.passed++;
  if (tests_vector_set()) passed.passed++;
  if (tests_vector_push()) passed.passed++;
  if (tests_vector_pop()) passed.passed++;
  if (tests_vector_clean()) passed.passed++;
  if (tests_vector_erase()) passed.passed++;
  if (tests_vector_copy()) passed.passed++;

  passed.all = 14;
  return passed;
}

char tests_vector_init() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));

  if (vec.cap == 1) passed.passed++;
  else printf("init cap failed\n");

  if (vec.size == 0) passed.passed++;
  else printf("init size failed\n");

  if (vec.size_of_el == sizeof(int)) passed.passed++;
  else printf("init sizeof failed\n");

  passed.all = 3;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_destroy() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  vector_destroy(&vec);

  if (vec.data == NULL) passed.passed++;
  else printf("destroy data not NULL\n");

  passed.all = 1;
  return passed.passed == passed.all;
}

char tests_vector_resize() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  unsigned int prev = vec.cap;

  vector_resize(&vec);

  if (vec.cap == prev * 2) passed.passed++;
  else printf("resize cap failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_reserve() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  vector_reserve(&vec, 5);

  if (vec.cap == 6) passed.passed++;
  else printf("reserve cap failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_fit() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  vector_fit(&vec, 12);

  if (vec.cap == 12) passed.passed++;
  else printf("fit cap failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_shrink() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));

  for (int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&i);

  vector_shrink(&vec);

  if (vec.cap == vec.size) passed.passed++;
  else printf("shrink cap != size\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_alloc() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));

  int a = 5;
  vector_alloc(&vec, (char*)&a, 10);

  if (vec.size == 10) passed.passed++;
  else printf("alloc size failed\n");

  int b;
  vector_get(&vec, (char*)&b, 5);
  if (b == 5) passed.passed++;
  else printf("alloc data failed\n");

  passed.all = 2;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_get() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  for (int i = 0; i < 10; i++)
    vector_push(&vec, (char*)&i);

  int v;
  vector_get(&vec, (char*)&v, 7);
  if (v == 7) passed.passed++;
  else printf("get failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_set() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  for (int i = 0; i < 10; i++)
    vector_push(&vec, (char*)&i);

  int x = 42;
  vector_set(&vec, (char*)&x, 5);

  int v;
  vector_get(&vec, (char*)&v, 5);
  if (v == 42) passed.passed++;
  else printf("set failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_push() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  int a = 3;
  vector_push(&vec, (char*)&a);

  int b;
  vector_get(&vec, (char*)&b, 0);
  if (b == 3) passed.passed++;
  else printf("push failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_pop() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  int a = 9;
  vector_push(&vec, (char*)&a);

  int b;
  vector_pop(&vec, (char*)&b);

  if (b == 9 && vec.size == 0) passed.passed++;
  else printf("pop failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_clean() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));
  for (int i = 0; i < 10; i++)
    vector_push(&vec, (char*)&i);

  vector_clean(&vec);

  if (vec.size == 0) passed.passed++;
  else printf("clean size failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_erase() {
  struct vector vec;
  struct passed passed = {0};

  vector_init(&vec, sizeof(int));

  for (int i = 0; i < 6; i++)
    vector_push(&vec, (char*)&i);

  vector_erase(&vec, 0, 2);

  int v;
  vector_get(&vec, (char*)&v, 0);
  if (v == 3) passed.passed++;
  else printf("erase failed\n");

  passed.all = 1;
  vector_destroy(&vec);
  return passed.passed == passed.all;
}

char tests_vector_copy() {
  struct vector v1, v2;
  struct passed passed = {0};

  vector_init(&v1, sizeof(int));
  vector_init(&v2, sizeof(int));

  for (int i = 0; i < 10; i++)
    vector_push(&v1, (char*)&i);

  vector_copy(&v1, &v2);

  int v;
  vector_get(&v2, (char*)&v, 7);
  if (v == 7) passed.passed++;
  else printf("copy failed\n");

  passed.all = 1;
  vector_destroy(&v1);
  vector_destroy(&v2);
  return passed.passed == passed.all;
}

#endif
