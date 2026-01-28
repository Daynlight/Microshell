/////////////////////////////////////////////////////////////
////////////////////////// Globals /////////////////////////
/////////////////////////////////////////////////////////////

struct string command;
struct path path;
struct string username;
struct string hostname;
char running;



/////////////////////////////////////////////////////////////
////////////////////////// Includes /////////////////////////
/////////////////////////////////////////////////////////////

#include <unistd.h>
#include <pwd.h>

#include "colors.h"
#include "Structures/String/string.h"
#include "Structures/Path/path.h"
#include "Commands/commands.h"



/////////////////////////////////////////////////////////////
////////////////////////// Initials /////////////////////////
/////////////////////////////////////////////////////////////

void get_username(){
  struct passwd *pw = getpwuid(getuid());

  if(pw)
    string_init_initial(&username, pw->pw_name);
  else
    string_init_initial(&username, "unknown");
};

void get_hostname(){
  char buffer[256];

  if (gethostname(buffer, sizeof(buffer)) == 0)
    string_init_initial(&hostname, buffer);
  else
    string_init_initial(&hostname, "unknown");
};

void init_globals(){
  string_init(&command);

  path_init(&path);
  path_cwd(&path);

  get_username();

  get_hostname();

  running = 1;
};

void destroy_globals(){
  path_destroy(&path);
  
  string_destroy(&username);
  string_destroy(&hostname);

  string_destroy(&command);

  running = 0;
};



/////////////////////////////////////////////////////////////
/////////////////////////// Helpers /////////////////////////
/////////////////////////////////////////////////////////////

void getUserInput(struct string* command){
  vector_clean(&command->data);

  char a = 0;
  while(a != '\n'){
    if(a != 0)
      vector_push(&command->data, (char*)(&a));
    a = getchar();
  };

  char el = 0;
  vector_push(&command->data, &el);
};



/////////////////////////////////////////////////////////////
/////////////////////// MainExecutable //////////////////////
/////////////////////////////////////////////////////////////

int main(int argc, char *argv[]){
  init_globals();

  while (running){
    printf(PATHCOLOR"[%s]: "USERCOLOR"%s@%s$ "CLEARCOLOR, path_get_ptr(&path), string_get_ptr(&username), string_get_ptr(&hostname));
    
    getUserInput(&command);
    runCommand(&command);
  };
    
  destroy_globals();

  return 0;
};
