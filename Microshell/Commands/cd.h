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

const char* moveDir(struct string *move){
  char buffer[255];
  buffer[0] = 0;
  int j = 0;

  for(int i = 0; i < move->data.size; i++){
    char el = string_get(move, i);

    if(el == '/'){
      if(j == 2 && buffer[0] == '.' && buffer[1] == '.'){
        char a = 0;
        int k = 0;
        while(a != '/'){
          a = string_get(&path, path.data.size - k);
          k++;
        };

        string_erase(&path, path.data.size - k + 1, 0);
      }
      else{
        string_concat(&path, "/");
        string_concat(&path, buffer);
      }
      

      buffer[0] = 0;
      j = 0;
      continue;
    }
    
    buffer[j] = string_get(move, i);
    buffer[j + 1] = 0;
    j++;
  };





  if(j == 2 && buffer[0] == '.' && buffer[1] == '.'){
    char a = 0;
    int k = 0;
    while(a != '/'){
      a = string_get(&path, path.data.size - k);
      k++;
    };

    string_erase(&path, path.data.size - k + 1, 0);
  }
  else{
    string_concat(&path, "/");
    string_concat(&path, buffer);
  };

  chdir(string_get_ptr(&path));
}; 


#endif