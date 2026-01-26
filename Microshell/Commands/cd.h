#ifndef CD_H
#define CD_H

#include <unistd.h>

#include "../Structures/String/string.h"
#include "../Structures/Vector/vector.h"
#include "../globals.h"


void setDir(const char* new_path){
  chdir(new_path);
  string_init_initial(&path, new_path);
};

#endif