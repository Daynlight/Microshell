#ifndef PATH_H
#define PATH_H

#include <unistd.h>
#include "../String/string.h"

struct path{
  struct string data;
};

void path_init(struct path* path){
  string_init(&path->data);
};

void path_init_initial(struct path* path, const char* data){
  string_init_initial(&path->data, data);
};

void path_init_initial_string(struct path* path, struct string* string){
  string_init_initial_string(&path->data, string);
};

void path_destroy(struct path* path){
  string_destroy(&path->data);
};

const char* path_get_ptr(struct path* path){
  return string_get_ptr(&path->data);
};

void path_set_string(struct path* path, struct string* string){
  string_destroy(&path->data);
  string_init_initial_string(&path->data, string);
};

void path_set(struct path* path, const char* data){
  string_destroy(&path->data);
  string_init_initial(&path->data, data);
};

void path_chdir(struct path* path){
  if(chdir(string_get_ptr(&path->data)) != 0){
    perror("chdir:");
  };
};

void path_cwd(struct path* path){
  char cwd[8192];

  if(getcwd(cwd, sizeof(cwd)) != NULL)
    string_init_initial(&path->data, cwd);
  else
    perror("getcwd");
};

void path_move(struct path* path, struct path* move){

};

#endif