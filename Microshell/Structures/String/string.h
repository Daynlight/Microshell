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

char string_get(const struct string* string, const unsigned int index);
void string_set(struct string* string, const char data, const unsigned int index);

void string_concat(struct string* dest, const char* src);
void string_concat_string(struct string* dest, const struct string* src);
int string_find(const struct string* string, const char* el);
void string_erase(struct string* string, const unsigned int x, const unsigned int y);

char* string_get_ptr(const struct string* string);











void string_init(struct string *string){
  vector_init(&string->data, sizeof(char));
};






void string_init_initial(struct string *string, const char *initial_data) {
  vector_init(&string->data, sizeof(char));
  unsigned int initial_data_size = strlen(initial_data);
  vector_reserve(&string->data, initial_data_size);
  for(int i = 0; i < initial_data_size; i++)
    vector_push(&string->data, &initial_data[i]);
};






inline void string_init_initial_string(struct string *string, const struct string *initial_data) {
  vector_copy(&initial_data->data, &string->data);
};






void string_destroy(struct string* string){
  vector_destroy(&string->data);
};






char string_get(const struct string* string, unsigned int index){
  char at = 0;
  vector_get(&string->data, &at, index);
  return at;
};






void string_set(struct string* string, char data, unsigned int index){
  vector_set(&string->data, &data, index);
};






inline void string_concat(struct string *dest, const char *src){
  struct string temp;
  string_init_initial(&temp, src);

  string_concat_string(dest, &temp);

  string_destroy(&temp);
};






void string_concat_string(struct string *dest, const struct string *src) {
  unsigned int previous_size = src->data.size;
  unsigned int additional_size = src->data.size;
  
  vector_reserve(&dest->data, additional_size);

  for(unsigned int i = 0; i < additional_size; i++){
    char at = string_get(src, i);
    vector_push(&dest->data, &at);
  };
};

int string_find(const struct string* string, const char* el){
  unsigned int i = 0;

  unsigned int el_size = strlen(el);
 
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






void string_erase(struct string* string, unsigned int x, unsigned int y){
  if(x > y){
    return;
  };

  unsigned int size = y - x + 1;
  unsigned int prev_size = string->data.size;

  memmove(string->data.data + x, string->data.data + y + 1, prev_size - y);
  char terminator[] = "\0";
  vector_set(&string->data, (char*)&terminator, prev_size - size);
  string->data.size -= size;
};






char* string_get_ptr( const struct string* string){
  return string->data.data;
};






#ifdef __cplusplus
}
#endif

#endif