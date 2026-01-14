#ifndef FLAGS_H
#define FLAGS_H

#include "Structures/String/string.h"
#include "globals.h"

void process_flags(int argc, char *argv[]){
  string_init_initial(&path, argv[0]);
};


#endif