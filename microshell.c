///////////////////////////
///////// Headers /////////
///////////////////////////
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>



///////////////////////////
////////// Macro //////////
///////////////////////////
#define VERSION "1.0.0"
#define AUTHOR "Daniel Stodulski"

// Colors
// 30 - Black
// 31 - Red
// 32 - Green
// 33 - Yellow
// 34 - Blue
// 35 - Magenta
// 36 - Cyan
// 37 - White
#define COLOR(x, c) "\033[0;"c"m"x"\033[0;37m"



///////////////////////////
///////// Globals /////////
///////////////////////////
char running = 1;



///////////////////////////
//////// Functions ////////
///////////////////////////
void microshellExit(){
  running = 0;
  printf(COLOR("\nMicroshell Exit!!\n", "31"));
  fflush(stdout);
}



void printInfo(){
  printf(COLOR("Info:\n", "33"));
  printf(COLOR("VERSION: "VERSION"\n", "32")
         COLOR("Author: "AUTHOR"\n", "32")
        "");

  fflush(stdout); 
};



void printFeatures(){
  printf(COLOR("Features:\n", "33"));
  printf(COLOR("* Text Coloring\n"
               "", "32"));

  fflush(stdout); 
};














void sigint_handler(int sig){
  microshellExit();
  exit(EXIT_FAILURE);
};



///////////////////////////
////// MainExecutable /////
///////////////////////////
int main(){
  signal(SIGINT, sigint_handler);

  printInfo();
  printFeatures();

  while (running) {
    char command[255] = {0};
    printf("$ ");
    scanf("%s", command);
    printf("\n");


    printf("%s", command);
  };
  

  return 0;
};