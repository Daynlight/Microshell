/////////////////////////////////////////////////////////////
////////////////////////// Includes /////////////////////////
/////////////////////////////////////////////////////////////

#include "Structures/Vector/vector.h"
#include "Structures/String/string.h"

#include "globals.h"

#include "flags.h"
#include "input.h"
#include "commands.h"

/////////////////////////////////////////////////////////////
/////////////////////// MainExecutable //////////////////////
/////////////////////////////////////////////////////////////
#include "Commands/cd.h"

int main(int argc, char *argv[]){
  init_globals();
  process_flags(argc, argv);
  
  struct string command;
  struct string move;
  string_init_initial(&move, "../../docs");
  // string_init_initial(&move, "/home");
  moveDir(&move);


  while (running){
    printf("\e[32m[%s]: \e[34m%s@%s$\e[0m ", string_get_ptr(&path), string_get_ptr(&username), string_get_ptr(&hostname));
    
    getUserInput(&command);

    runCommand(&command);

  };
  

  
  destroy_globals();

  return 0;
};
