//////////////////////////
///////// vector /////////
//////////////////////////
//// IDEA ////
// A vector is a dynamic array that can grow when needed.
// It lets us store data even when we don't know how many elements we will need.
// Useful for unordered_map, paths, lists, and more.

//// How it works: ////
// A vector keeps two numbers:
//   * size     — how many elements are currently stored
//   * capacity — how much space is allocated
//
// When adding elements:
//   * If size < capacity, we just insert the new element.
//   * If size == capacity, we need more room:
//       - allocate a new larger buffer
//       - copy all existing elements to it
//       - free the old buffer
//       - replace it with the new one
//
// This allows the vector to grow dynamically
// as long as the system has memory available.

//// TL;TR ////
// * When capacity is full, allocate a larger buffer,
//   copy elements, and continue using the new one.


#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif



struct vector{
  unsigned int cap;
  unsigned int size;
  unsigned int size_of_el;
  char* data;
};

void vector_init(struct vector* vector, unsigned int size_of_el);
void vector_destroy(struct vector* vector);

void vector_resize(struct vector* vector);
void vector_reserve(struct vector* vector, unsigned int cap);

void vector_emplace_back(struct vector* vector, char* data);
void vector_pop(struct vector* vector, char* out);

void vector_get(struct vector* vector, char* out, unsigned int index);
void vector_set(struct vector* vector, char* data, unsigned int index);

void vector_alloc(struct vector* vector, unsigned int size, char* data);













void vector_init(struct vector* vector, unsigned int size_of_el){
  vector->size_of_el = size_of_el;
  vector->data = (char*)calloc(1, vector->size_of_el);
  vector->cap = 1;
  vector->size = 0;
};






void vector_destroy(struct vector* vector){
  free(vector->data);
  vector->data = NULL;
};






void vector_resize(struct vector* vector) {
  unsigned int new_cap = vector->cap * 2 + 1; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};






void vector_reserve(struct vector *vector, unsigned int cap){
  unsigned int new_cap = vector->cap + cap; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};






void vector_emplace_back(struct vector *vector, char *data){
  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};





void vector_pop(struct vector* vector, char* out){
  vector_get(vector, out, vector->size - 1);
  vector->size--;
};





void vector_get(struct vector* vector, char* out, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_get error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};






void vector_set(struct vector* vector, char* data, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_set error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(vector->data + offset, data, vector->size_of_el);
};






void vector_alloc(struct vector *vector, unsigned int size, char *data){
  unsigned int missing_space = 2 * vector->size + size - vector->cap;
  vector_reserve(vector, missing_space);
  for(int i = 0; i < size; i++)
    vector_emplace_back(vector, data);
};




#ifdef __cplusplus
}
#endif

#endif
