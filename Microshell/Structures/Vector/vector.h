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

void vector_push(struct vector* vector, const char* data);
void vector_pop(struct vector* vector, char* out);

void vector_get(const struct vector* vector, char* out, const unsigned int index);
void vector_set(struct vector* vector, const char* data, unsigned int index);

void vector_alloc(struct vector* vector, unsigned int size, char* data);
void vector_copy(const struct vector* src, struct vector* dest);













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






void vector_push(struct vector *vector, const char *data){
  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};





void vector_pop(struct vector* vector, char* out){
  vector_get(vector, out, vector->size - 1);
  vector->size--;
};





void vector_get(const struct vector* vector, char* out, const unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_get error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};






void vector_set(struct vector* vector, const char* data, unsigned int index){
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
    vector_push(vector, data);
};






inline void vector_copy(const struct vector *src, struct vector *dest) {
  dest->size_of_el = src->size_of_el;
  dest->cap = src->cap;
  dest->size = src->size;
  
  dest->data = (char*)calloc(dest->cap, dest->size_of_el);

  memcpy(dest->data, src->data, src->size * src->size_of_el);
};






#ifdef __cplusplus
}
#endif

#endif
