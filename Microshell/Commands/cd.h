#ifndef CD_H
#define CD_H

#include <unistd.h>

#include "../Structures/String/string.h"
#include "../Structures/Vector/vector.h"
#include "../globals.h"


void setDir(const char* new_path){
  chdir(new_path);
  string_destroy(&path);
  string_init_initial(&path, new_path);
};

void moveDir(struct string *move){
  struct string new_path;
    
  if(string_get(move, 0) == '/')
    string_init_initial_string(&new_path, move);
  else{
    string_init_initial_string(&new_path, &path);
    char s[2] = "/";
    if(string_get(&path, path.data.size - 1) != '/')
      string_concat(&new_path, s);
    string_concat_string(&new_path, move);
    // string_concat(&new_path, s);
  };

  chdir(string_get_ptr(&new_path));


  char cwd[4098];

  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    string_init_initial(&path, cwd);
  } else {
    perror("getcwd");
  }
}; 


#endif