#ifndef INPUT_H
#define INPUT_H

#include "Structures/String/string.h"


void getUserInput(struct string* command){
  string_destroy(command);
  string_init(command);

  string_erase(command, 0, -1);

  char a = 0;
  while(a != '\n'){
    if(a != 0)
      vector_push(&command->data, (char*)(&a));
    a = getchar();
  };
};




#endif