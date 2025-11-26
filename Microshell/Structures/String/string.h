

#ifndef STRING_H
#define STRING_H


#ifdef __cplusplus
extern "C" {
#endif


#include "../Vector/vector.h"


struct string{
  struct vector data;
};

void string_init(struct string* string, char* initial_data);
void string_destroy(struct string* string);

char string_at(struct string* string, unsigned int index);
void string_set(struct string* string, char data, unsigned int index);

void string_concat(struct string* string, struct string* string2);
int string_find(struct string* string, char el);
void string_erase(struct string* string, unsigned int x, unsigned int y);













void string_init(struct string* string, char* initial_data){
  vector_init(&string->data, sizeof(char));
  unsigned int initial_data_size = strlen(initial_data);
  vector_reserve(&string->data, initial_data_size);
  for(int i = 0; i < initial_data_size; i++)
    vector_push(&string->data, &initial_data[i]);
};






void string_destroy(struct string* string){
  vector_destroy(&string->data);
};






char string_at(struct string* string, unsigned int index){
  char at = 0;
  vector_get(&string->data, &at, index);
  return at;
};






void string_set(struct string* string, char data, unsigned int index){
  vector_set(&string->data, &data, index);
};






void string_concat(struct string* string, struct string* string2){
  unsigned int previous_size = string->data.size;
  unsigned int additional_size = string2->data.size;
  
  vector_reserve(&string->data, additional_size);

  for(unsigned int i = 0; i < additional_size; i++){
    char at = string_at(string2, i);
    vector_push(&string->data, &at);
  };
};






int string_find(struct string* string, char el){
  char found = 0;
  unsigned int i = 0;
  do{
    char at = string_at(string, i);
    if(at == el)
      return i;
    
    i++;
  }
  while(i < string->data.size && !found);  
  
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






char* string_get_ptr(struct string* string){
  return string->data.data;
};






#ifdef __cplusplus
}
#endif

#endif