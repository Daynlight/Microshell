/////////////////////////////////////////////////////////////////////////
///////////////////////// Architecture Overview /////////////////////////
/////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////
///////////////// Structures //////////////////
///////////////////////////////////////////////
//////////////////////////
///////// vector /////////
//////////////////////////
//// IDEA ////
// Vector is dynamic array that allows 
// storing dynamic data that can change with time
// We want it for unordered_map and string.
//// Functions: ////
// * init
// * destroy
// * reserve
// * resize
// * push
// * pop
// * erase
// * get
// * set
//// Optimization: ////
// * reserve - optimization for large data


//////////////////////////
///////// string /////////
//////////////////////////
//// IDEA ////
// Dynamic string with no size limitation
// We don't know path size and we need strings to dynamicly
// operate on them without it we waste a lot of memory
// and can it cause mem overflow
// In this project:
// Used for saving dynamic size names and path.
//// Functions: ////
// * init
// * destroy
// * concat
// * at
// * find
// * erase
// * get_ptr
// Optimization:
// * store data in continsuse array on heap
// * that heap memory is char* and we can use it to iteration


//////////////////////////
////////// path //////////
//////////////////////////
//// IDEA ////
// Dynamic array of strings that contains folders and provide 
// build path


///////////////////////////////////////////////
/////////////////// Logic /////////////////////
///////////////////////////////////////////////
// String class is Decorated from Vector
// Path class is Decorated from Vector





//////////////////////////////////////////////////////////////////
//////////////////////////// Headers /////////////////////////////
//////////////////////////////////////////////////////////////////
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



///////////////////////////////////////////////////////////////////
////////////////////////////// Macro //////////////////////////////
///////////////////////////////////////////////////////////////////
#define VERSION "1.0.0"
#define AUTHOR "Daniel Stodulski"

#define MAXDIRSIZE 255
#define MAXDEPTH 32
#define MAXUSERNAME 255

#define COMMANDSIZE 100

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



/////////////////////////////////////////////////////////////////////////
///////////////////////// Additional Structures /////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////////////
///////// vector /////////
//////////////////////////
struct vector{
  unsigned int cap;
  unsigned int size;
  unsigned int size_of_el;
  char* data;
};

void vector_init(struct vector* vector, unsigned int size_of_el){
  vector->size_of_el = size_of_el;
  vector->data = calloc(1, vector->size_of_el);
  vector->cap = 1;
  vector->size = 0;
};

void vector_reserve(struct vector* vector, unsigned int cap){
  unsigned int new_cap = vector->cap + cap; 
  char* temp = calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};

void vector_destroy(struct vector* vector){
  free(vector->data);
};

void vector_resize(struct vector* vector) {
  unsigned int new_cap = vector->cap * 2 + 1; 
  char* temp = calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};

void vector_push(struct vector* vector, char* data){
  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};

void vector_pop(struct vector* vector, char* out){
  if (vector->size == 0) {
    fprintf(stderr, "Error: cannot pop from empty vector\n");
    return;
  };

  vector->size--;
  memcpy(out, vector->data + vector->size * vector->size_of_el, vector->size_of_el);
};

void vector_get(struct vector* vector, char* out, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_get error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};

void vector_set(struct vector* vector, char* data, unsigned int index){
  if(index >= vector->size) {
    fprintf(stderr, "vector_set error: index %u out of range (size=%u)\n",
            index, vector->size);
    return;
  };
  unsigned int offset = index * vector->size_of_el;
  memcpy(vector->data + offset, data, vector->size_of_el);
};


//////////////////////////
///////// string /////////
//////////////////////////
struct string{
  struct vector data;
};

void string_init(struct string* string, char* initial_data){

};

void string_destroy(struct string* string){

};

void string_concat(struct string* string){

};

void string_at(struct string* string, unsigned int index){

};

void string_find(struct string* string, char el){

};

void string_erase(struct string* string, unsigned int x, unsigned int y){

};

void string_get_ptr(struct string* string){

};






/////////////////////////////////////////////////////////
//////////////////////// Globals ////////////////////////
/////////////////////////////////////////////////////////
char running = 1;
struct vector path_vector;
char path_string[MAXDEPTH * MAXDIRSIZE] = {0};
char* username_string;



/////////////////////////////////////////////////////////
/////////////////////// Functions ///////////////////////
/////////////////////////////////////////////////////////
void microshellExit(){
  running = 0;
  printf(COLOR("Microshell Exit!!\n", "31"));
  fflush(stdout);
}



///////////////
//// print ////
///////////////
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
               "* Current Path\n"
               "* User Name\n", "32"));

  fflush(stdout); 
};

void printCommands(){
  printf(COLOR("Commands:\n", "33"));
  printf(COLOR("* help - show command list and info\n"
               "* exit - exit from microshell\n", "32"));

  fflush(stdout); 
};



//////////////////
//// UserName ////
/////////////////
void getUserName(){
  username_string = getlogin();
};



//////////////
//// Path ////
//////////////
void pathToVector(char* current_path){
  unsigned int current_path_size = strlen(current_path);
  char folder[MAXDIRSIZE] = {0};

  for(int i = 0; i < current_path_size; i++){
    if(current_path[i] != '/'){
      char ch[2] = {0};
      ch[0] = current_path[i];
      strcat(folder, &ch[0]);
    }
    else{
      if(strncmp(folder, "..", 2) == 0){
        if(path_vector.size >= 1){
          char temp[MAXDIRSIZE];
          vector_pop(&path_vector, temp);
        }
      }
      else{
        vector_push(&path_vector, folder);
      }
      memset(folder, 0, MAXDIRSIZE);
    };
  };
  
  vector_push(&path_vector, folder);
};

void pathToString(){
  memset(path_string, 0 , MAXDIRSIZE * MAXDEPTH);

  for(int i = 0; i < path_vector.size; i++){
    strcat(path_string, "/");

    char directory[MAXDIRSIZE] = {0};
    vector_get(&path_vector, directory, i);
    strcat(path_string, directory);
  };

  if(path_vector.size <= 0)
    strcat(path_string, "/");

  path_string[strlen(path_string)] = '\0';
};

void getCurrentPath(){
  vector_destroy(&path_vector);
  vector_init(&path_vector, MAXDIRSIZE);
  
  char current_path[MAXDIRSIZE * MAXDEPTH] = "";
  getcwd(current_path, MAXDIRSIZE * MAXDEPTH);

  pathToVector(current_path);
  pathToString();
};



//////////////////
//// Commands ////
//////////////////
void commandCd(char* command){
  char path[MAXDIRSIZE * MAXDEPTH] = {0};
  strncpy(path, command + 3, MAXDIRSIZE * MAXDEPTH);
  printf("%s\n", path);
  path[strlen(path) - 1] = '/';

  pathToVector(path);

  // if(path_vector.size > 0 && strcmp(path, "..") == 0){
  //     char temp[MAXDIRSIZE];
  //     vector_pop(&path_vector, temp);
  //   };

  // if(chdir(path) != 0){
  //   printf(COLOR("Error: No such file or directory\n", "31"));
  //   fflush(stdout);
  // };

  pathToString();
};

void commandParser(char* command){
  if(strncmp(command, "exit", 4) == 0){
    microshellExit();
    exit(EXIT_SUCCESS);
  }
  else if(strncmp(command, "help", 4) == 0){
    printInfo();
    printFeatures();
    printCommands();  
  }
  else if(strncmp(command, "cd", 2) == 0){
    commandCd(command);
  }
  else{

  }
};



////////////////
//// Helper ////
////////////////
void sigint_handler(int sig){
  printf("\n");
  microshellExit();
  exit(EXIT_SUCCESS);
};










/////////////////////////////////////////////////////////////
/////////////////////// MainExecutable //////////////////////
/////////////////////////////////////////////////////////////
#ifndef HEADER 
int main(){
  signal(SIGINT, sigint_handler);

  getUserName();
  getCurrentPath();
  printInfo();
  printFeatures();

  while (running) {
    char command[COMMANDSIZE] = {0};
    printf("[%s](%s) $ ", path_string, username_string);
    fgets(command, COMMANDSIZE, stdin);

    commandParser(command);
  };
  
  microshellExit();

  return 0;
};
#endif