#ifndef COMMANDS_H
#define COMMANDS_H

#include <unistd.h>
#include <sys/wait.h>

#include "Structures/String/string.h"
#include "Structures/Vector/vector.h"

#include "Commands/exit.h"
#include "Commands/help.h"




void runUnknow(struct string* command){
  char* argv[255];
  int j = 0;
  int k = 0;

  argv[j] = malloc(255);

  for(int i = 0; i < command->data.size; i++){
    char a = string_get(command, i);
    
    if(a == ' '){
      argv[j][k] = '\0';
      j++;
      k = 0;
      argv[j] = malloc(255);
      continue;
    }

    argv[j][k] = a;
    k++;
  };
  
  argv[j][k] = '\0';
  argv[j + 1] = NULL;

  pid_t pid = fork();

  if (pid == 0){
    execvp(argv[0], argv);
    fprintf(stderr, "\e[91m");
    fprintf(stderr, "Command: %s\n", string_get_ptr(command));
    perror("");
    fprintf(stderr, "\e[00m");
    exit(1);
  }
  else if (pid > 0){
    wait(NULL);
  }
  else{
    perror("fork");
  }

  for(int i = 0; i <= j; i++){
    free(argv[i]);
  }

};


void runCommand(struct string* command){

  if(strcmp(string_get_ptr(command), "exit") == 0)
    commands_exit();
  else if(strcmp(string_get_ptr(command), "help") == 0)
    commands_help();
  else
    runUnknow(command);

};





#endif