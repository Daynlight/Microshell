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


#ifndef COLORS_H
#define COLORS_H

/////////////////////////////////////////////////////////////
/////////////////////////// COLORS //////////////////////////
/////////////////////////////////////////////////////////////

#define CLEARCOLOR "\e[0m"
#define PATHCOLOR "\e[1;32m"
#define USERCOLOR "\e[1;34m"
#define HELPCOLOR "\e[1;33m"

#endif


#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct vector{
  unsigned int cap;
  unsigned int size;
  unsigned int size_of_el;
  char* data;
};

void vector_init(struct vector* vector, const unsigned int size_of_el);
void vector_destroy(struct vector* vector);

void vector_resize(struct vector* vector);
void vector_reserve(struct vector* vector, const unsigned int additional_cap);
void vector_shrink(struct vector* vector);
void vector_alloc(struct vector* vector, const char* data, const unsigned int size);
void vector_fit(struct vector* vector, const unsigned int size);

void vector_push(struct vector* vector, const char* data);
void vector_pop(struct vector* vector, char* out);

void vector_erase(struct vector* vector, const int x, const int y);
void vector_clean(struct vector* vector);

void vector_get(const struct vector* vector, char* out, const unsigned int index);
void vector_set(struct vector* vector, const char* data, const unsigned int index);
void vector_copy(const struct vector* src, struct vector* dest);













void vector_init(struct vector* vector, const unsigned int size_of_el){
  if(size_of_el <= 0)
    return;

  vector->size_of_el = size_of_el;
  vector->cap = 1;
  vector->size = 0;
  vector->data = (char*)calloc(vector->cap, vector->size_of_el);

  if(vector->data == NULL)
    return;
};






void vector_destroy(struct vector* vector){
  if(vector->data != NULL){
    free(vector->data);
    vector->data = NULL;
  };
};






void vector_resize(struct vector* vector) {
  if(vector->data == NULL)
    return;

  unsigned int new_cap = vector->cap * 2; 
  
  if(new_cap <= 0) 
    new_cap = 1;
  
  char* temp = (char*)calloc(new_cap, vector->size_of_el);

  if(temp == NULL)
    return;
  
  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);
    
  vector->data = temp;
  vector->cap = new_cap;

  if(vector->data == NULL)
    return;
};






void vector_reserve(struct vector *vector, const unsigned int additional_cap){
  if(vector->data == NULL)
    return;

  if(additional_cap <= 0)
    return;

  unsigned int new_cap = vector->cap + additional_cap; 
  
  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  if(temp == NULL)
    return;

  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;
  
  if(vector->data == NULL)
    return;
};






void vector_shrink(struct vector *vector){
  if(vector->data == NULL)
    return;

  unsigned int new_cap = vector->size; 

  if(new_cap <= 0)
    new_cap = 1;

  char* temp = (char*)calloc(new_cap, vector->size_of_el);
  
  if(temp == NULL)
    return;

  memcpy(temp, vector->data, vector->size * vector->size_of_el);
  free(vector->data);

  vector->data = temp;
  vector->cap = new_cap;

  if(vector->data == NULL)
    return;
};






void vector_alloc(struct vector *vector, const char *data, const unsigned int size){
  if(vector->data == NULL)
    return;

  if(size <= 0)
    return;

  unsigned int prev_size = vector->size; 
  vector_fit(vector, size);
  
  for(int i = prev_size; i < vector->cap; i++)
    vector_push(vector, data);
};






void vector_fit(struct vector *vector, const unsigned int size){
  if(vector->data == NULL)
    return;

  if(size <= vector->size)
    return;

  unsigned int missing_space = 2 * vector->size + size - vector->cap;
  vector_reserve(vector, missing_space);
};







void vector_push(struct vector *vector, const char *data){
  if(vector->data == NULL)
    return;

  if(vector->size >= vector->cap)
    vector_resize(vector);
  
  memcpy(vector->data + vector->size * vector->size_of_el, data, vector->size_of_el);
  vector->size++;
};





void vector_pop(struct vector* vector, char* out){
  if(vector->data == NULL)
    return;

  if(vector->size <= 0)
    return;

  vector_get(vector, out, vector->size - 1);
  vector->size--;
};





void vector_erase(struct vector *vector, const int x, const int y){
  if(vector->data == NULL)
    return;

  if(vector->size <= 0)
    return;

  int p_x = (x % vector->size + vector->size) % vector->size;
  int p_y = (y % vector->size + vector->size) % vector->size;
  
  unsigned int size = p_y - p_x + 1;
  unsigned int prev_size = vector->size;

  if(p_x > p_y){
    vector_erase(vector, p_x, vector->size - 1);
    vector_erase(vector, 0, p_y);
  }
  else{
    memmove(vector->data + p_x * vector->size_of_el, vector->data + (p_y + 1) * vector->size_of_el, (prev_size - p_y) * vector->size_of_el);
    vector->size -= size;
  };

};





void vector_clean(struct vector *vector)
{
  if(vector->data == NULL)
    return;

  free(vector->data);
  vector->data = (char*)calloc(vector->cap, vector->size_of_el);

  vector->size = 0;

  if(vector->data == NULL)
    return;
};

void vector_get(const struct vector* vector, char* out, const unsigned int index){
  if(vector->data == NULL)
    return;

  if(index >= vector->size)
    return;

  unsigned int offset = index * vector->size_of_el;
  memcpy(out, vector->data + offset, vector->size_of_el);
};






void vector_set(struct vector* vector, const char* data, const unsigned int index){
  if(vector->data == NULL)
    return;

  if(index >= vector->size)
    return;

  unsigned int offset = index * vector->size_of_el;
  memcpy(vector->data + offset, data, vector->size_of_el);
};







void vector_copy(const struct vector *src, struct vector *dest) {
  if(dest->data == NULL || src->data == NULL)
    return;

  dest->size_of_el = src->size_of_el;
  dest->cap = src->cap;
  dest->size = src->size;
  
  dest->data = (char*)calloc(dest->cap, dest->size_of_el);

  memcpy(dest->data, src->data, src->size * src->size_of_el);

  if(dest->data == NULL)
    return;
};


#endif



#ifndef STRING_H
#define STRING_H



struct string{
  struct vector data;
};

void string_init(struct string* string);
void string_init_initial(struct string* string, const char* initial_data);
void string_init_initial_string(struct string* string, const struct string* initial_data);

void string_destroy(struct string* string);

const char string_get(const struct string* string, const unsigned int index);
void string_set(struct string* string, const char data, const unsigned int index);

void string_concat(struct string* dest, const char* src);
void string_concat_string(struct string* dest, const struct string* src);
const int string_find(const struct string* string, const char* el);
void string_erase(struct string* string, const int x, const int y);

const char* string_get_ptr(const struct string* string);











void string_init(struct string *string){
  vector_init(&string->data, sizeof(char));
  vector_push(&string->data, (char*)&"\0");
};






void string_init_initial(struct string *string, const char *initial_data) {
  vector_init(&string->data, sizeof(char));
  unsigned int initial_data_size = strlen(initial_data);
  vector_reserve(&string->data, initial_data_size);
  
  for(int i = 0; i < initial_data_size; i++)
    vector_push(&string->data, &initial_data[i]);

  char el;
  vector_get(&string->data, &el, string->data.size - 1);
  if(el != 0)
    vector_push(&string->data, (char*)&"\0");

};






void string_init_initial_string(struct string *string, const struct string *initial_data) {
  string_init(string);
  vector_copy(&initial_data->data, &string->data);
};






void string_destroy(struct string* string){
  vector_destroy(&string->data);
};






const char string_get(const struct string* string, const unsigned int index){
  if(index >= string->data.size)
    return 0;

  char at = 0;
  vector_get(&string->data, &at, index);
  return at;
};






void string_set(struct string* string, const char data, const unsigned int index){
  if(index >= string->data.size)
    return;

  vector_set(&string->data, &data, index);
};






void string_concat(struct string *dest, const char *src){
  if(strlen(src) <= 1)
    return;
  
  struct string temp;
  string_init_initial(&temp, src);

  string_concat_string(dest, &temp);

  string_destroy(&temp);
};






void string_concat_string(struct string *dest, const struct string *src) {
  if(src->data.size <= 0)
    return;

  unsigned int additional_size = src->data.size;

  vector_reserve(&dest->data, additional_size);

  char el;
  vector_pop(&dest->data, &el);

  for(unsigned int i = 0; i < additional_size; i++){
    char at = string_get(src, i);
    vector_push(&dest->data, &at);
  };

  vector_shrink(&dest->data);
};






const int string_find(const struct string* string, const char* el){
  unsigned int i = 0;
  unsigned int el_size = strlen(el);

  if(el_size > string->data.size)
    return -1;

 
  char found = 0;

  do{
    found = 1;

    for(int j = 0; j < el_size; j++){
      char at = string_get(string, i + j);
      if(el[j] != at){
        found = 0;
        continue;
      };
    };

    if(found)
      return i;
    
    i++;
  }
  while(found == 0 && i < string->data.size - el_size + 1);  
  
  return -1;
};






void string_erase(struct string* string, const int x, const int y){
  if(!string && string->data.size <= 0)
    return;

  vector_erase(&string->data, x, y);

  vector_shrink(&string->data);
};







const char* string_get_ptr(const struct string* string){
  return string->data.data;
};






#endif

#ifndef PATH_H
#define PATH_H

#include <unistd.h>

struct path{
  struct string data;
};

void path_init(struct path* path);
void path_init_initial_string(struct path* path, struct string* string);
void path_init_initial(struct path* path, const char* data);
void path_destroy(struct path* path);

const char* path_get_ptr(struct path* path);
void path_set_string(struct path* path, struct string* string);

void path_remove_last(struct path* path);
int path_chdir(struct path* path);
void path_cwd(struct path* path);
void path_move(struct path* path, struct string* move);
void path_remove_last(struct path* path);




void path_init(struct path* path){
  const char st[] = "/";
  path_init_initial(path, st);
};







void path_init_initial(struct path* path, const char* data){
  struct string new_path;
  string_init_initial(&new_path, data);
  
  path_init_initial_string(path, &new_path);

  string_destroy(&new_path);
};






void path_init_initial_string(struct path* path, struct string* string){
  struct string new_path;
  string_init(&new_path);

  struct string sep;
  string_init_initial(&sep, "/");

  if(string->data.size <= 1 || string->data.data[0] != '/')
    string_concat_string(&new_path, &sep);

  string_concat_string(&new_path, string);

  if(string->data.data[string->data.size - 2] != '/')
    string_concat_string(&new_path, &sep);

  string_init_initial_string(&path->data, &new_path);

  string_destroy(&new_path);
};





void path_destroy(struct path* path){
  string_destroy(&path->data);
};






const char* path_get_ptr(struct path* path){
  return string_get_ptr(&path->data);
};






void path_set_string(struct path* path, struct string* string){
  path_destroy(path);

  struct string new_path;
  string_init(&new_path);
  
  path_init_initial_string(path, string);
};






void path_set(struct path* path, const char* data){
  path_destroy(path);

  string_init_initial(&path->data, data);
};






int path_chdir(struct path* path){
  const char* p = path_get_ptr(path);
  if(chdir(p) != 0){
    perror("chdir:");
    return -1;
  };

  return 0;
};

void path_cwd(struct path* path){
  char cwd[8192];

  if(getcwd(cwd, sizeof(cwd)) != NULL)
    string_init_initial(&path->data, cwd);
  else
    perror("getcwd");

  struct string temp;
  string_init_initial(&temp, "/");
  string_concat_string(&path->data, &temp);
  string_destroy(&temp);
};






void path_move(struct path* path, struct string* move){
  struct vector buffer;
  vector_init(&buffer, sizeof(char));
  char el;

  vector_pop(&move->data, &el);

  int a = -1;
  el = ' ';
  while(el == ' '){
    a++;
    vector_get(&move->data, &el, a);
  };

  if(a > 0)
    vector_erase(&move->data, 0, a - 1);


  vector_get(&move->data, &el, move->data.size - 1);
  if(el != '/'){
    el = '/';
    vector_push(&move->data, &el);
  };

  for (int i = 0; i < move->data.size; i++){
    vector_get(&move->data, &el, i);
    if(el == 0){}
    else if(el == '/'){
      if(strcmp(buffer.data, "..") == 0)
        path_remove_last(path);
      else{
        el = '/';
        vector_push(&buffer, &el);
        struct string temp;
        string_init_initial(&temp, buffer.data);
        string_concat_string(&path->data, &temp);
        string_destroy(&temp);
      }

      vector_clean(&buffer);
    }
    else
      vector_push(&buffer, &el);
  };
  
  vector_destroy(&buffer);


  if(path_chdir(path)){
    path_cwd(path);
  };
};






void path_remove_last(struct path* path){
  char el;
  vector_pop(&path->data.data, &el);
  vector_pop(&path->data.data, &el);

  if(el == '/') el = 0;

  if(path->data.data.size != 0)
    while(path->data.data.size > 0 && el != '/')
      vector_pop(&path->data.data, &el);

  el = '/';
  vector_push(&path->data.data, &el);
  el = 0;
  vector_push(&path->data.data, &el);
};

#endif


#ifndef EXIT_H
#define EXIT_H

void commands_exit(){
  running = 0;
};

#endif

#ifndef HELP_H
#define HELP_H

#include <stdio.h>

void commands_help(){
  printf(HELPCOLOR);
  printf(R"(
========================
====== Microshell ======
========================

========================
Author: Daniel Stodulski
========================
commands:
* exit - exit from program.
* help - show help and info about author.
* cd - move between directories.
* cwd - show curent working directory.
* cls - clear terminal.

)");
printf(CLEARCOLOR);
};


#endif


#ifndef COMMANDS_H
#define COMMANDS_H

/////////////////////////////////////////////////////////////
////////////////////////// Includes /////////////////////////
/////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/wait.h>



/////////////////////////////////////////////////////////////
///////////////////////// Functions /////////////////////////
/////////////////////////////////////////////////////////////


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
  };
};


void runCommand(struct string* command){

  if(strcmp(string_get_ptr(command), "exit") == 0)
    commands_exit();

  else if(strcmp(string_get_ptr(command), "help") == 0)
    commands_help();

  else if(command->data.size >= 3 && 
          command->data.data[0] == 'c' && 
          command->data.data[1] == 'd' && 
          command->data.data[2] == ' '){
    struct string move;
    string_init_initial_string(&move, command);
    string_erase(&move, 0, 2);
    
    path_move(&path, &move);

    string_destroy(&move);
  }

  else if(strcmp(string_get_ptr(command), "cwd") == 0){
    struct path temp;
    path_init(&temp);
    path_cwd(&temp);
    printf("cwd: %s\n", path_get_ptr(&temp));
    path_destroy(&temp);
  }

  else if(strcmp(string_get_ptr(command), "cls") == 0)
    printf("\033[H\033[J");

  else
    runUnknow(command);

};

#endif



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
