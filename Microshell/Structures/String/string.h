#ifndef STRING_H
#define STRING_H


#ifdef __cplusplus
extern "C" {
#endif


#include "../Vector/vector.h"


struct string{
  struct vector data;
};

void string_init(struct string* string);
void string_init_initial(struct string* string, const char* initial_data);
void string_init_initial_string(struct string* string, const struct string* initial_data);

void string_destroy(struct string* string);

const char string_get(const struct string* string, const unsigned int index);
void string_set(struct string* string, const char data, const unsigned int index);

void string_concat(struct string* dest, const char* src);
void string_concat_string(struct string* dest, const struct string* src);
const int string_find(const struct string* string, const char* el);
void string_erase(struct string* string, const int x, const int y);

const char* string_get_ptr(const struct string* string);











void string_init(struct string *string){
  vector_init(&string->data, sizeof(char));
  vector_push(&string->data, (char*)&"\0");
};






void string_init_initial(struct string *string, const char *initial_data) {
  vector_init(&string->data, sizeof(char));
  unsigned int initial_data_size = strlen(initial_data);
  vector_reserve(&string->data, initial_data_size);
  
  for(int i = 0; i < initial_data_size; i++)
    vector_push(&string->data, &initial_data[i]);
};






void string_init_initial_string(struct string *string, const struct string *initial_data) {
  vector_copy(&initial_data->data, &string->data);
};






void string_destroy(struct string* string){
  vector_destroy(&string->data);
};






const char string_get(const struct string* string, const unsigned int index){
  if(index >= string->data.size)
    return 0;

  char at = 0;
  vector_get(&string->data, &at, index);
  return at;
};






void string_set(struct string* string, const char data, const unsigned int index){
  if(index >= string->data.size)
    return;

  vector_set(&string->data, &data, index);
};






void string_concat(struct string *dest, const char *src){
  if(strlen(src) <= 0)
    return;
  
  struct string temp;
  string_init_initial(&temp, src);

  string_concat_string(dest, &temp);

  string_destroy(&temp);
};






void string_concat_string(struct string *dest, const struct string *src) {
  if(src->data.size <= 0)
    return;

  unsigned int additional_size = src->data.size;

  vector_reserve(&dest->data, additional_size);

  for(unsigned int i = 0; i < additional_size; i++){
    char at = string_get(src, i);
    vector_push(&dest->data, &at);
  };

  vector_shrink(&dest->data);
};






const int string_find(const struct string* string, const char* el){
  unsigned int i = 0;
  unsigned int el_size = strlen(el);

  if(el_size > string->data.size)
    return -1;

 
  char found = 0;

  do{
    found = 1;

    for(int j = 0; j < el_size; j++){
      char at = string_get(string, i + j);
      if(el[j] != at){
        found = 0;
        continue;
      };
    };

    if(found)
      return i;
    
    i++;
  }
  while(found == 0 && i < string->data.size - el_size + 1);  
  
  return -1;
};






void string_erase(struct string* string, const int x, const int y){
  if(!string && string->data.size <= 0)
    return;

  vector_erase(&string->data, x, y);

  vector_shrink(&string->data);
};






const char* string_get_ptr(const struct string* string){
  return string->data.data;
};






#ifdef __cplusplus
}
#endif

#endif