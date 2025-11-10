///////////////////////////
///////// Headers /////////
///////////////////////////
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



///////////////////////////
////////// Macro //////////
///////////////////////////
#define VERSION "1.0.0"
#define AUTHOR "Daniel Stodulski"
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



/////////////////////////////////////////
///////// Additional Structures /////////
/////////////////////////////////////////
//////////////////////////
///////// vector /////////
//////////////////////////
//// IDEA ////
//  We have structure vector that contains
// information about vector and pointer to
// our data
//  On add if we don't have enough space
// we resize vector by creating new and 
// coping data from previous, then deleting
// old one and swap with new one
//  Data can be any type soo we have
// to use char*
// For add element we have to cast type to
// char* and copy them to next free cell 
// For getting element we need to calculate
// offset = index * size_of_el then copy it
// to out char*
//// TL;TR ////
// * We have to use char* for operate on any type
// * When we don't have enough space just resize

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

void vector_emplace_back(struct vector* vector, char* data){
  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
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



/////////////////////////
///// unordered_map /////
/////////////////////////
//// IDEA ////
// We have vector with data
// We have also buckets and hash function
// When element add we:
// 1) add element to vector and save index
// 2) calculate hash for element in our situation cahr[COMMANDSIZE]
// 4) calculate hash % buckets
// 5) add index with char[COMMANDSIZE] to bucket
// When we search for el:
// 1) we calculate hash for element
// 2) calculate hash % buckets
// 3) search for element in bucket
// 4) if found return index else -1
//// TL;TR ////
// * We create buckets where we store references to index in array
// * This makes search O(1)






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



///////////////////////////
///////// Helpers /////////
///////////////////////////
void sigint_handler(int sig){
  microshellExit();
  exit(EXIT_FAILURE);
};



///////////////////////////
////// MainExecutable /////
///////////////////////////
#ifndef HEADER 
int main(){
  signal(SIGINT, sigint_handler);

  printInfo();
  printFeatures();

  while (running) {
    char command[COMMANDSIZE] = {0};
    printf("$ ");
    scanf("%s", command);
    printf("\n");


    printf("%s", command);
  };
  
  microshellExit();

  return 0;
};
#endif