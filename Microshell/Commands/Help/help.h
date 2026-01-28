#ifndef HELP_H
#define HELP_H

#include <stdio.h>

void commands_help(){
  printf(HELPCOLOR);
  printf(R"(
========================
====== Microshell ======
========================

========================
Author: Daniel Stodulski
========================
commands:
* exit - exit from program.
* help - show help and info about author.
* cd - move between directories.
* cwd - show curent working directory.
* cls - clear terminal.

)");
printf(CLEARCOLOR);
};


#endif