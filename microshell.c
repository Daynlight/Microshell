/////////////////////////////////////////////////////////////////////////
///////////////////////// Architecture Overview /////////////////////////
/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
///////////////////////// Structures //////////////////////////
///////////////////////////////////////////////////////////////
// vector *, string *, path, prefix array, unordered_map *, deque, stack //

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
// * shrink ^
// * fit    ^
// * push
// * pop
// * erase
// * clean  ^
// * get
// * set
// * alloc


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
// * set
// * get_ptr


/////////////////////////
///// unordered_map /////
/////////////////////////
//// IDEA ////
// We want a fast way to find the value from a kay.
// An unordered_map gives O(1) average lookup time,
// so it is fast to finding values from keys.
//// Functions: ////
// * init
// * destroy
// * get
// * set


////////////////////////
///// prefix array /////
////////////////////////
//// IDEA ////
//// Functions: ////


///////////////////////////
////////// deque //////////
///////////////////////////
//// IDEA ////
//// Functions: ////


///////////////////////////
////////// stack //////////
///////////////////////////
//// IDEA ////
//// Functions: ////


//////////////////////////
////////// path //////////
//////////////////////////
//// IDEA ////
// Dynamic array of strings that contains folders and provide 
// whole path
//// Functions: ////




///////////////////////////////////////////////////////////////
//////////////////////////// TODO /////////////////////////////
///////////////////////////////////////////////////////////////
//// Structures ////
// [x] Use String
// [ ] Path Struct
// [ ] Dequeue Struct
// [ ] Stack Struct
// [ ] Prefix Array Struct
// [ ] Update program to use new structures

//// MVP ////
// [x] Workflow for every system (Cross-Platform update)
// [ ] Architecture Overview logic part
// [ ] Input Handler
// [ ] Input Controller
// [ ] Command Composer
// [ ] Command Parser
// [ ] Command Runner
// [ ] Task Queue
// [ ] Task Controller
// [ ] Env Register
// [x] UI Colorer 
// [ ] UI Composer
// [ ] Ui Printer
// [ ] ```Ctrl + Z``` process exit or program

//// Requirements ////
// [x] User name
// [x] ^ encouragement sign {path} $
// [ ] ^ cd
// [x] ^ exit
// [ ] ^ execute form PATH: ```fork + exec*()```
// [ ] ^ Error Comuniact: When can't parsee command
// [x] ^ help: Info + Features + Commands

//// Features ////
// [ ] Data I/O
// [ ] History Controller
// [ ] Prefix Controller
// [ ] Data Controller
// [ ] Command Predictor
// [ ] Autocomplete with the most relevant
// [ ] Task Result
// [ ] Task Error Handler
// [ ] UI Error Handler
// [ ] coloring text for params, "", (), {}. [].
// [ ] arrows for history/autocomplete
// [ ] ^ two more commands
// [ ] cp
// [ ] Windows integration (Cross-Platform update)






















#ifdef __cplusplus
extern "C" {
#endif


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

#define KEYSIZE 32
#define BUCKETS 10























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
  vector->data = (char*)calloc(1, vector->size_of_el);
  vector->cap = 1;
  vector->size = 0;
};

void vector_destroy(struct vector* vector){
  free(vector->data);
  vector->data = NULL;
};

void vector_resize(struct vector* vector) {
  unsigned int new_cap = vector->cap * 2 + 1; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};

void vector_reserve(struct vector *vector, unsigned int cap){
  unsigned int new_cap = vector->cap + cap; 
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
};

void vector_push(struct vector *vector, char *data){
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

void vector_pop(struct vector* vector, char* out){
  vector_get(vector, out, vector->size - 1);
  vector->size--;
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

void vector_alloc(struct vector *vector, unsigned int size, char *data){
  unsigned int missing_space = 2 * vector->size + size - vector->cap;
  vector_reserve(vector, missing_space);
  for(int i = 0; i < size; i++)
    vector_push(vector, data);
};



//////////////////////////
///////// string /////////
//////////////////////////
struct string{
  struct vector data;
};

void string_init(struct string* string, char* initial_data){
  vector_init(&string->data, sizeof(char));
  unsigned int initial_data_size = strlen(initial_data);
  vector_reserve(&string->data, initial_data_size);
  for(int i = 0; i < initial_data_size; i++)
    vector_push(&string->data, &initial_data[i]);
};

void string_destroy(struct string* string){
  vector_destroy(&string->data);
};

char string_at(struct string* string, unsigned int index){
  char at = 0;
  vector_get(&string->data, &at, index);
  return at;
};

void string_set(struct string* string, char data, unsigned int index){
  vector_set(&string->data, &data, index);
};

void string_concat(struct string* string, struct string* string2){
  unsigned int previous_size = string->data.size;
  unsigned int additional_size = string2->data.size;
  
  vector_reserve(&string->data, additional_size);

  for(unsigned int i = 0; i < additional_size; i++){
    char at = string_at(string2, i);
    vector_push(&string->data, &at);
  };
};

int string_find(struct string* string, char el){
  char found = 0;
  unsigned int i = 0;
  do{
    char at = string_at(string, i);
    if(at == el)
      return i;
    
    i++;
  }
  while(i < string->data.size && !found);  
  
  return -1;
};

void string_erase(struct string* string, unsigned int x, unsigned int y){
  if(x > y){
    return;
  };

  unsigned int size = y - x + 1;
  unsigned int prev_size = string->data.size;

  memmove(string->data.data + x, string->data.data + y + 1, prev_size - y);
  char terminator[] = "\0";
  vector_set(&string->data, (char*)&terminator, prev_size - size);
  string->data.size -= size;
};

char* string_get_ptr(struct string* string){
  return string->data.data;
};


/////////////////////////
///// unordered_map /////
/////////////////////////
struct bucket_record{
  char key[KEYSIZE];                  // key
  unsigned int index;                 // localization
};

struct unordered_map{
  struct vector data;                 // real data
  struct vector buckets[BUCKETS];     // type of bucket_record
};


unsigned int unordered_map_hash_fun(const char* key){
  unsigned int hash = 5381;
  int c;
  
  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }
  
  return hash;
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

int unordered_map_get(struct unordered_map* unordered_map, char* out, const char* key){
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

void unordered_map_set(struct unordered_map* unordered_map, char* data, const char* key){
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
    vector_push(&unordered_map->buckets[bucket_id], (char*)&record);
    vector_push(&unordered_map->data, data);
  }
  else{                                                     // found
    vector_set(&unordered_map->data, data, index);
  };
};


/////////////////////////
///////// path //////////
/////////////////////////


//////////////////////////
///////// dequeue ////////
//////////////////////////


//////////////////////////
///////// stack //////////
//////////////////////////


/////////////////////////////////
///////// prefix array //////////
/////////////////////////////////


























/////////////////////////////////////////////////////////
//////////////////////// Globals ////////////////////////
/////////////////////////////////////////////////////////
char running = 1;
struct string path;
struct string username;



///////////////////////////////////////////////////////////
///////////////////////////// UI //////////////////////////
///////////////////////////////////////////////////////////
/////////////////////////////////////////////////
///////////////////// UI COLOR //////////////////
/////////////////////////////////////////////////
enum COLORS{
  BLACK = 30,
  RED = 31,
  Green = 32,
  Yellow = 33,
  Blue = 34,
  Magenta = 35,
  Cyan = 36,
  White = 37
};

const char* COLOR(const char* str, enum COLORS color){
  const unsigned int length = strlen(str) + 2 + 8 + 10;
  char *colored = (char*)calloc(length, sizeof(char));
  sprintf(colored, "\033[0;%dm%s\033[0;37m", color, str);   // [BUG] mem loss
  return colored;
};







/////////////////////////////////////////////////////////
/////////////////////// Functions ///////////////////////
/////////////////////////////////////////////////////////
void microshellExit(){
  running = 0;
  string_destroy(&path);
  string_destroy(&username);
  printf(COLOR("Microshell Exit!!\n", RED));
  fflush(stdout);
}



///////////////
//// print ////
///////////////
void printInfo(){
  printf(COLOR("Info:\n", Green));
  printf(COLOR("VERSION: " VERSION "\n", RED));
  printf(COLOR("Author: " AUTHOR "\n", RED));

  fflush(stdout); 
};

void printFeatures(){
  printf(COLOR("Features:\n", Green));
  printf(COLOR("* Text Coloring\n"
               "* Current Path\n"
               "* User Name\n", RED));

  fflush(stdout); 
};

void printCommands(){
  printf(COLOR("Commands:\n", Green));
  printf(COLOR("* help - show command list and info\n"
               "* exit - exit from microshell\n", RED));

  fflush(stdout); 
};



//////////////////
//// UserName ////
/////////////////
void getUserName(){
  char* username_temp = getlogin();
  string_destroy(&username);
  string_init(&username, username_temp);
};



//////////////
//// Path ////
//////////////
void getCurrentPath(){
  string_destroy(&path);
  string_init(&path, "");
  char* data = "\0";
  vector_alloc(&path.data, MAXDIRSIZE * MAXDEPTH, data);

  getcwd(string_get_ptr(&path), MAXDIRSIZE * MAXDEPTH);
};



//////////////////
//// Commands ////
//////////////////

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

  string_init(&path, "");
  string_init(&username, "");

  getUserName();
  getCurrentPath();

  printInfo();
  printFeatures();

  while (running) {
    struct string command;
    string_init(&command, "");    // [NOTE] suboptimal
    printf("[%s](%s) $ ", string_get_ptr(&path), string_get_ptr(&username));
    
    
    fgets(string_get_ptr(&command), COMMANDSIZE, stdin);

    
    commandParser(string_get_ptr(&command));
    string_destroy(&command);
  };
  
  microshellExit();

  return 0;
};
#endif


#ifdef __cplusplus
}
#endif
