#ifndef GLOBALS_H
#define GLOBALS_H

#include "Structures/String/string.h"

static struct string path;
static char running;



void init_globals(){
  string_init(&path);
  running = 1;
};

void destroy_globals(){
  string_destroy(&path);
  running = 0;
};

#endif