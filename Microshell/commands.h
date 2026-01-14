#ifndef COMMANDS_H
#define COMMANDS_H

#include "Structures/String/string.h"

#include "Commands/exit.h"
#include "Commands/help.h"

void runCommand(struct string* command){

  if(strcmp(string_get_ptr(command), "exit") == 0)
    commands_exit();
  else if(strcmp(string_get_ptr(command), "help") == 0)
    commands_help();

};





#endif