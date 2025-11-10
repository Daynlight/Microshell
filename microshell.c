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
#define KEYSIZE 100
#define BUCKETS 10

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
//// Note ////
// We dont need whole unordered_map for searching we just need to check
// if it exists, but I want implement unordered_map for learning purposes 
// hash_fun now is simple better would be sha256 better hash => better buckets distribution

struct bucket_record{
  char key[KEYSIZE];                  // key
  unsigned int index;                 // localization
};

struct unordered_map{
  struct vector data;                 // real data
  struct vector buckets[BUCKETS];     // type of bucket_record
};

unsigned int unordered_map_hash_fun(const char* key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = (hash * 33) + hash + c;

    return (unsigned int)hash;
};

void unordered_map_init(struct unordered_map* unordered_map, unsigned int size_of_el){
  vector_init(&unordered_map->data, size_of_el);
  for(int i = 0; i < BUCKETS; i++)
    vector_init(&unordered_map->buckets[i], sizeof(struct bucket_record));
};

void unordered_map_destroy(struct unordered_map* unordered_map){
  vector_destroy(&unordered_map->data);
  for(int i = 0; i < BUCKETS; i++)
    vector_destroy(&unordered_map->buckets[i]);
};

int unordered_map_get(struct unordered_map* unordered_map, char* out, char* key){
  unsigned int hash = unordered_map_hash_fun(key);
  unsigned int bucket_id = hash % BUCKETS;

  unsigned int index = 0;
  for(int i = 0; i < unordered_map->buckets[bucket_id].size; i++){    // look for key in bucket
    index = i;
    
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, i);

    if(strcmp(record.key, key) == 0)
      break;
    else
      index++;
  }

  if(index >= unordered_map->buckets[bucket_id].size){  // don't found
    return -1;
  }
  else{                                                     // found
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, index);
    vector_get(&unordered_map->data, out, record.index);
  };
  return 0;
};

void unordered_map_set(struct unordered_map* unordered_map, char* data, char* key){
  unsigned int hash = unordered_map_hash_fun(key);
  unsigned int bucket_id = hash % BUCKETS;

  unsigned int index = 0;
  for(int i = 0; i < unordered_map->buckets[bucket_id].size; i++){    // look for key in bucket
    index = i;
    
    struct bucket_record record;
    vector_get(&unordered_map->buckets[bucket_id], (char*)&record, i);

    if(strcmp(record.key, key) == 0)
      break;
    else
      index++;
  }

  if(index >= unordered_map->buckets[bucket_id].size){  // don't found
    struct bucket_record record;
    record.index = unordered_map->data.size;
    memcpy(record.key, key, KEYSIZE);
    vector_emplace_back(&unordered_map->buckets[bucket_id], (char*)&record);
    vector_emplace_back(&unordered_map->data, data);
  }
  else{                                                     // found
    vector_set(&unordered_map->data, data, index);
  };
};



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