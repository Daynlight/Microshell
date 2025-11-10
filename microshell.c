///////////////////////////
///////// Headers /////////
///////////////////////////
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



///////////////////////////
////////// Macro //////////
///////////////////////////
#define VERSION "1.0.0"
#define AUTHOR "Daniel Stodulski"

#define MAXDIRSIZE 255
#define MAXDEPTH 32
#define MAXUSERNAME 255

#define COMMANDSIZE 100

#define KEYSIZE 100
#define BUCKETS 10

// Colorsf
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
// Vector is dynamic array that allows 
// storing dynamic data that can change with time
// We want it for unordered_map, path, etc.

//// How it works: ////
// We have data and we don't know how much we have left
// We add element as long as we have space
// If we use all of our space we just create next 
// bigger buffer and copy data to them. After that
// we delete old buffer and swap with new one.
// In this way we have unlimited memory to use.

//// TL;TR ////
// * When we use all of space we have just create new bigger want and swap them

//// In this project: ////
// * Used for unordered_map for storing commands and paths.
// * For our current path.

//// Optimization: ////
// * [NOTE] reserve function
// * [NOTE] cache size to file and use this info to reserve at start

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
// We want fast way to find path from command
// unordered_map allow us to make fast lookup
// soo it is prefect structure to use

//// How it works: ////
// First we create vector with our real data
// in this case paths to commands
// Now to find path from command we have to 
// iterate through them.
// We will store additional informations in
// buckets. Bucket is vector where we store 
// keys and index to data in our main data
// vector. Now we add hash function when we
// want to find data instead of iterate
// through all of them we hash key and 
// make modulo BUCKETS to find bucket
// where key is stored. Hashing always
// gives the same results soo for the
// same name we always access the same bucket
// Instead of iterate for every element we
// iterate only in one bucket.
// More buckets = less iterations.
// Also quality of hash is important
// if hash is good then we separate keys in
// better way and we have less iteration to do.

//// TL;TR ////
// * We hash key and save them with index to real data in bucket
// * When we search for them we only search in one bucket

//// In this project: ////
// In this project we use unordered_map to store comands as keys
// and paths to executables. Every key is unique.

//// Addition ////
// [Hash map with SHA256](https://github.com/Daynlight/CCrypt/blob/main/CCrypt/Struct/unordered_map.h)

//// Optimization: ////
// * [NOTE] Better hash

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
struct vector path_vector;
char path_string[MAXDEPTH * MAXDIRSIZE] = {0};
char* username_string;


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


void getUserName(){
  username_string = getlogin();
};


void pathToVector(char* current_path){
  unsigned int current_path_size = strlen(current_path);
  char folder[MAXDIRSIZE] = {0};

  for(int i = 1; i < current_path_size; i++){
    if(current_path[i] != '/'){
      strcat(folder, &current_path[i]);
    }
    else{
      vector_emplace_back(&path_vector, folder);
      memset(folder, 0, MAXDIRSIZE);
    };
  };
};

void pathToString(){
  for(int i = 1; i < path_vector.size; i++){
    strcpy(path_string, "/");
    char directory[MAXDIRSIZE] = {0};
    vector_get(&path_vector, directory, i);
    strcpy(path_string, directory);
  };
  path_string[strlen(path_string)] = '\0';
};

void getCurrentPath(){
  vector_destroy(&path_vector);
  vector_init(&path_vector, sizeof(MAXDIRSIZE));
  
  char current_path[MAXDIRSIZE * MAXDEPTH] = "";
  getcwd(current_path, MAXDIRSIZE * MAXDEPTH);

  pathToVector(current_path);
  memcpy(path_string, current_path, strlen(current_path));
};


///////////////////////////
////// MainExecutable /////
///////////////////////////
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
    scanf("%s", command);
    printf("\n");


    printf("%s\n", command);
  };
  
  microshellExit();

  return 0;
};
#endif