#pragma once 

#include "Assert.h"


namespace Structures::UnitTests{
class Vector{
private:
  Tests::Assert assert;
public:
  bool runAll();
  
  void vectorInit();
  void vectorDestroy();

  void vectorResize();
  void vectorReserve();
  void vectorShrink();
  void vectorAlloc();
  void vectorFit();

  void vectorPush();
  void vectorPop();

  void vectorErase();
  void vectorClean();

  void vectorSet();
  void vectorGet();

  void vectorCopy();
};











bool Vector::runAll(){
  printf("==== Vector Tests ====\n");

  vectorInit();
  vectorDestroy();
  
  vectorResize();
  vectorReserve();
  vectorShrink();
  vectorAlloc();
  vectorFit();

  vectorGet();
  vectorSet();

  vectorErase();
  vectorClean();
  
  vectorPush();
  vectorPop();
  vectorCopy();

  return assert.results("Vector");
};






void Vector::vectorInit() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  assert.equal("Vector::vectorInit cap", vec.cap, 1);
  assert.equal("Vector::vectorInit size", vec.size, 0);
  assert.equal("Vector::vectorInit size_of_el", vec.size_of_el, sizeof(int));
  assert.isNotNullptr("Vector::vectorInit data", vec.data);

  vector_destroy(&vec);
};






void Vector::vectorDestroy() {
  struct vector vec;
  vector_init(&vec, sizeof(int));
  vector_destroy(&vec);

  assert.isNullptr("Vector::vectorDestroy data", vec.data);
};






void Vector::vectorResize() {
  struct vector vec;
  vector_init(&vec, sizeof(int));
  unsigned int prev_cap = vec.cap;
  unsigned int estimated_cap = prev_cap * 2;

  vector_resize(&vec);
  unsigned int new_cap = vec.cap;

  assert.equal("Vector::vectorResize cap", new_cap, estimated_cap);
  assert.notEqual("Vector::vectorResize cap", new_cap, prev_cap);

  vector_destroy(&vec);
};






void Vector::vectorReserve() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  unsigned int additional_cap = 5;
  unsigned int prev_cap = vec.cap;
  unsigned int estimated_cap = prev_cap + additional_cap;

  vector_reserve(&vec, additional_cap);
  unsigned int new_cap = vec.cap;

  assert.equal("Vector::vectorReserve cap", new_cap, estimated_cap);
  assert.notEqual("Vector::vectorReserve cap", new_cap, prev_cap);

  vector_destroy(&vec);
};






void Structures::UnitTests::Vector::vectorFit(){
  struct vector vec;
  vector_init(&vec, sizeof(int));

  vector_fit(&vec, 12);

  assert.equal("Vector::vectorFit cap", vec.cap, 12);
  vector_destroy(&vec);
};






void Structures::UnitTests::Vector::vectorShrink(){
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++){
    vector_push(&vec, (char*)&i);
  };

  vector_reserve(&vec, 20);

  assert.notEqual("Vector::vectorShrink cap != size", vec.cap, vec.size);

  vector_shrink(&vec);

  assert.equal("Vector::vectorShrink cap == size", vec.cap, vec.size);

  vector_destroy(&vec);
};






void Vector::vectorAlloc() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a = 5;
  unsigned int elements = 20;
  
  unsigned int prev_size = vec.size;
  unsigned int prev_cap = vec.cap;
  unsigned int estimated_size = prev_size + elements;
  unsigned int estimated_cap = prev_size + elements;

  vector_alloc(&vec, (char*)&a, elements);


  assert.equal("Vector::vectorAlloc size", vec.size, estimated_size);
  assert.equal("Vector::vectorAlloc cap", vec.cap, estimated_cap);
  
  for(int i = prev_size; i < estimated_size; i++){
    int b = 0;
    vector_get(&vec, (char*)&b, i);
    assert.equal("Vector::vectorAlloc data", b, a);
  };


  vector_destroy(&vec);
};






void Vector::vectorGet() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&i);

  
  for(int i = 0; i < 20; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorGet", a, i);
  };

  vector_destroy(&vec);
};







void Vector::vectorSet() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&i);

  for(int i = 0; i < 20; i++){
    int a = 20 - i;
    vector_set(&vec, (char*)&a, i);
  };
  
  for(int i = 0; i < 20; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorSet", a, 20 - i);
  };

  vector_destroy(&vec);
};







void Vector::vectorPop() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  for(int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&i);
  
  

  int a = 0;
  vector_pop(&vec, (char*)&a);
  assert.equal("Vector::vectorPop data", a, 19);
  assert.equal("Vector::vectorPop size", vec.size, 19);

  vector_destroy(&vec);
};







void Vector::vectorPush() {
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a[20];
  int b[20] = {0};

  for(int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&a[i]);
  
  for(int i = 0; i < 20; i++)
    vector_get(&vec, (char*)&b[i], i);
  
  for(int i = 0; i < 20; i++)
    assert.equal("Vector::vectorPush", b[i], a[i]);

  vector_destroy(&vec);
};







void Structures::UnitTests::Vector::vectorClean(){
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a[20];

  for(int i = 0; i < 20; i++)
    vector_push(&vec, (char*)&a[i]);

  assert.equal("Vector::vectorClean size", vec.size, 20);
  assert.equal("Vector::vectorClean cap", vec.cap, 32);

  vector_clean(&vec);

  assert.equal("Vector::vectorClean size", vec.size, 0);
  assert.equal("Vector::vectorClean cap", vec.cap, 32);  
};







void Structures::UnitTests::Vector::vectorErase(){
  struct vector vec;
  vector_init(&vec, sizeof(int));

  int a[6] = {0, 1, 2, 3, 4, 5};
  int c1[3] = {3, 4, 5};
  int c2 = 4;

  for(int i = 0; i < 6; i++)
    vector_push(&vec, (char*)&a[i]);

  vector_erase(&vec, 0, 2);

  for(int i = 0; i < 3; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorErase 1", a, c1[i]);
  };

  vector_erase(&vec, -1, 0);

  for(int i = 0; i < 1; i++){
    int a = 0;
    vector_get(&vec, (char*)&a, i);
    assert.equal("Vector::vectorErase 2", a, c2);
  }


  vector_destroy(&vec);
};







void Vector::vectorCopy() {
  struct vector vec1;
  vector_init(&vec1, sizeof(int));

  struct vector vec2;
  vector_init(&vec2, sizeof(int));

  int a[20];
  for(int i = 0; i < 20; i++)
    vector_push(&vec1, (char*)&a[i]);

  vector_copy(&vec1, &vec2);

  for(int i = 0; i < 20; i++){
    int b = 0;
    vector_get(&vec2, (char*)&b, i);
    assert.equal("Vector::vectorCopy", b, a[i]);
  }

  vector_destroy(&vec2);
  vector_destroy(&vec1);
};
};