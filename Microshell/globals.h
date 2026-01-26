#ifndef GLOBALS_H
#define GLOBALS_H

#include <unistd.h>
#include <pwd.h>
#include "Structures/String/string.h"

static struct string path;
static struct string username;
static struct string hostname;
static char running;



void init_globals(){
  string_init(&path);

  struct passwd *pw = getpwuid(getuid());
  string_init_initial(&username, pw ? pw->pw_name : "unknown");
  
  char buffer[256];

  if (gethostname(buffer, sizeof(buffer)) == 0)
    string_init_initial(&hostname, buffer);
  else
    string_init_initial(&hostname, "unknown");

  running = 1;
};

void destroy_globals(){
  string_destroy(&path);
  string_destroy(&username);
  string_destroy(&hostname);
  running = 0;
};

#endif