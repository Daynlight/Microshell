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

void vector_init(struct vector* vector, const unsigned int size_of_el);
void vector_destroy(struct vector* vector);

void vector_resize(struct vector* vector);
void vector_reserve(struct vector* vector, const unsigned int additional_cap);
void vector_shrink(struct vector* vector);
void vector_alloc(struct vector* vector, const char* data, const unsigned int size);
void vector_fit(struct vector* vector, const unsigned int size);

void vector_push(struct vector* vector, const char* data);
void vector_pop(struct vector* vector, char* out);

void vector_get(const struct vector* vector, char* out, const unsigned int index);
void vector_set(struct vector* vector, const char* data, const unsigned int index);
void vector_copy(const struct vector* src, struct vector* dest);













void vector_init(struct vector* vector, const unsigned int size_of_el){
  if(size_of_el <= 0)
    return;

  vector->size_of_el = size_of_el;
  vector->cap = 1;
  vector->size = 0;
  vector->data = (char*)calloc(vector->cap, vector->size_of_el);

  if(vector->data == NULL)
    return;
};






void vector_destroy(struct vector* vector){
  if(vector->data != NULL){
    free(vector->data);
    vector->data = NULL;
  };
};






void vector_resize(struct vector* vector) {
  if(vector->data == NULL)
    return;

  unsigned int new_cap = vector->cap * 2; 
  
  if(new_cap <= 0) 
    new_cap = 1;
  
  char* temp = (char*)calloc(new_cap, vector->size_of_el);

  if(temp == NULL)
    return;
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);
    
  vector->data = temp;
  vector->cap = new_cap;

  if(vector->data == NULL)
    return;
};






void vector_reserve(struct vector *vector, const unsigned int additional_cap){
  if(vector->data == NULL)
    return;

  if(additional_cap <= 0)
    return;

  unsigned int new_cap = vector->cap + additional_cap; 
  
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  if(temp == NULL)
    return;

  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
  
  if(vector->data == NULL)
    return;
};






void vector_shrink(struct vector *vector){
  if(vector->data == NULL)
    return;

  unsigned int new_cap = vector->size; 

  if(new_cap <= 0)
    new_cap = 1;

  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  if(temp == NULL)
    return;

  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;

  if(vector->data == NULL)
    return;
};






void vector_alloc(struct vector *vector, const char *data, const unsigned int size){
  if(vector->data == NULL)
    return;

  if(size <= 0)
    return;

  unsigned int prev_size = vector->size; 
  vector_fit(vector, size);
  
  for(int i = prev_size; i < vector->cap; i++)
    vector_push(vector, data);
};






void vector_fit(struct vector *vector, const unsigned int size){
  if(vector->data == NULL)
    return;

  if(size <= vector->size)
    return;

  unsigned int missing_space = 2 * vector->size + size - vector->cap;
  vector_reserve(vector, missing_space);
};







void vector_push(struct vector *vector, const char *data){
  if(vector->data == NULL)
    return;

  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};





void vector_pop(struct vector* vector, char* out){
  if(vector->data == NULL)
    return;

  if(vector->size <= 0)
    return;

  vector_get(vector, out, vector->size - 1);
  vector->size--;
};





void vector_get(const struct vector* vector, char* out, const unsigned int index){
  if(vector->data == NULL)
    return;

  if(index >= vector->size)
    return;

  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};






void vector_set(struct vector* vector, const char* data, const unsigned int index){
  if(vector->data == NULL)
    return;

  if(index >= vector->size)
    return;

  unsigned int offset = index * vector->size_of_el;
  memcpy(vector->data + offset, data, vector->size_of_el);
};







void vector_copy(const struct vector *src, struct vector *dest) {
  if(dest->data == NULL || src->data == NULL)
    return;

  dest->size_of_el = src->size_of_el;
  dest->cap = src->cap;
  dest->size = src->size;
  
  dest->data = (char*)calloc(dest->cap, dest->size_of_el);

  memcpy(dest->data, src->data, src->size * src->size_of_el);

  if(dest->data == NULL)
    return;
};






#ifdef __cplusplus
}
#endif

#endif
