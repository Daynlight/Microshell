#ifndef HELP_H
#define HELP_H

#include <stdio.h>

void commands_help(){
  printf("\e[33m");
  printf(R"(Microshell
========================
Author: Daniel Stodulski

========================
commands:
- exit - exit from program.

)");
printf("\e[00m");
};


#endif