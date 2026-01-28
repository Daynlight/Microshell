#ifndef PATH_H
#define PATH_H

#include <unistd.h>
#include "../String/string.h"

struct path{
  struct string data;
};

void path_init(struct path* path);
void path_init_initial_string(struct path* path, struct string* string);
void path_init_initial(struct path* path, const char* data);
void path_destroy(struct path* path);

const char* path_get_ptr(struct path* path);
void path_set_string(struct path* path, struct string* string);

void path_remove_last(struct path* path);
int path_chdir(struct path* path);
void path_cwd(struct path* path);
void path_move(struct path* path, struct string* move);
void path_remove_last(struct path* path);




void path_init(struct path* path){
  const char st[] = "/";
  path_init_initial(path, st);
};







void path_init_initial(struct path* path, const char* data){
  struct string new_path;
  string_init_initial(&new_path, data);
  
  path_init_initial_string(path, &new_path);

  string_destroy(&new_path);
};






void path_init_initial_string(struct path* path, struct string* string){
  struct string new_path;
  string_init(&new_path);

  struct string sep;
  string_init_initial(&sep, "/");

  if(string->data.size <= 1 || string->data.data[0] != '/')
    string_concat_string(&new_path, &sep);

  string_concat_string(&new_path, string);

  if(string->data.data[string->data.size - 2] != '/')
    string_concat_string(&new_path, &sep);

  string_init_initial_string(&path->data, &new_path);

  string_destroy(&new_path);
};





void path_destroy(struct path* path){
  string_destroy(&path->data);
};






const char* path_get_ptr(struct path* path){
  return string_get_ptr(&path->data);
};






void path_set_string(struct path* path, struct string* string){
  path_destroy(path);

  struct string new_path;
  string_init(&new_path);
  
  path_init_initial_string(path, string);
};






void path_set(struct path* path, const char* data){
  path_destroy(path);

  string_init_initial(&path->data, data);
};






int path_chdir(struct path* path){
  const char* p = path_get_ptr(path);
  if(chdir(p) != 0){
    perror("chdir:");
    return -1;
  };

  return 0;
};

void path_cwd(struct path* path){
  char cwd[8192];

  if(getcwd(cwd, sizeof(cwd)) != NULL)
    string_init_initial(&path->data, cwd);
  else
    perror("getcwd");

  struct string temp;
  string_init_initial(&temp, "/");
  string_concat_string(&path->data, &temp);
  string_destroy(&temp);
};






void path_move(struct path* path, struct string* move){
  struct vector buffer;
  vector_init(&buffer, sizeof(char));
  char el;

  vector_pop(&move->data, &el);

  int a = -1;
  el = ' ';
  while(el == ' '){
    a++;
    vector_get(&move->data, &el, a);
  };

  if(a > 0)
    vector_erase(&move->data, 0, a - 1);


  vector_get(&move->data, &el, move->data.size - 1);
  if(el != '/'){
    el = '/';
    vector_push(&move->data, &el);
  };

  for (int i = 0; i < move->data.size; i++){
    vector_get(&move->data, &el, i);
    if(el == 0){}
    else if(el == '/'){
      if(strcmp(buffer.data, "..") == 0)
        path_remove_last(path);
      else{
        el = '/';
        vector_push(&buffer, &el);
        struct string temp;
        string_init_initial(&temp, buffer.data);
        string_concat_string(&path->data, &temp);
        string_destroy(&temp);
      }

      vector_clean(&buffer);
    }
    else
      vector_push(&buffer, &el);
  };
  
  vector_destroy(&buffer);


  if(path_chdir(path)){
    path_cwd(path);
  };
};






void path_remove_last(struct path* path){
  char el;
  vector_pop(&path->data.data, &el);
  vector_pop(&path->data.data, &el);

  if(el == '/') el = 0;

  if(path->data.data.size != 0)
    while(path->data.data.size > 0 && el != '/')
      vector_pop(&path->data.data, &el);

  el = '/';
  vector_push(&path->data.data, &el);
  el = 0;
  vector_push(&path->data.data, &el);
};

#endif