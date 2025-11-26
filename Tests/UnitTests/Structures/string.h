#pragma once 
#include "Assert.h"


namespace Structures::UnitTests{
class String{
private:
  Tests::Assert assert;
public:
  bool runAll();
  
  void stringInit();
  void stringInitInitialCharPtr();
  void stringInitInitialString();
  void stringDestroy();

  void stringConcat();
  void stringAt();
  void stringFind();
  void stringErase();
  void stringSet();
  void stringGetPtr();
};











inline bool String::runAll(){
  printf("==== String Tests ====\n");

  stringInit();
  stringInitInitialString();
  stringInitInitialCharPtr();
  stringDestroy();
  stringConcat();
  stringAt();
  stringSet();
  stringFind();
  stringErase();
  stringGetPtr();

  return assert.results("String");
};











inline void String::stringInit(){
  struct string string;
  string_init(&string);

  
  assert.equal("String::stringInit size", string.data.size, 0);
  assert.equal("String::stringInit size", string.data.cap, 1);
  assert.isNotNullptr("String::stringInit data", (const char*)&string.data);
  assert.equal("String::stringInit size", string.data.size_of_el, sizeof(char));


  string_destroy(&string);
};






inline void String::stringInitInitialCharPtr(){
  struct string string;
  char initial[] = "Hello World";
  string_init_initial(&string, initial);

  assert.isNotNullptr("String::stringInitInitialCharPtr data", (const char*)&string.data);

  for(int i = 0; i < string.data.size; i++){
    char at = string_at(&string, i);
    assert.equal("String::stringInitInitialCharPtr iteration", at, initial[i]);
  }

  string_destroy(&string);
};






inline void String::stringInitInitialString() {
  struct string string;
  char initial[] = "Hello World";
  string_init_initial(&string, initial);

  struct string string2;
  string_init_initial_string(&string2, &string);

  assert.isNotNullptr("String::stringInitInitialCharPtr data", (const char*)&string2.data);

  for(int i = 0; i < string2.data.size; i++){
    char at = string_at(&string2, i);
    assert.equal("String::stringInitInitialCharPtr iteration", at, initial[i]);
  }

  string_destroy(&string);
};






inline void String::stringDestroy() {
  struct string string;
  char initial[] = "Hello World";
  string_init_initial(&string, initial);
  string_destroy(&string);
  assert.isNullptr("String::stringDestroy data", string.data.data);
};






inline void String::stringConcat() {
  struct string string;
  char initial[] = "Hello ";
  struct string string2;
  char initial2[] = "World";
  char complete[] = "Hello World";
  
  string_init_initial(&string, initial);
  string_init_initial(&string2, initial2);
  string_concat(&string, &string2);

  for(int i = 0; i < string.data.size; i++){
    char at = string_at(&string, i);
    assert.equal("String::stringConcat iteration", at, complete[i]);
  };

  string_destroy(&string);
};






inline void String::stringAt() {
  struct string string;
  char initial[] = "Hello World";
  string_init_initial(&string, initial);

  char at = string_at(&string, 3);
  assert.equal("String::stringAt at 3", at, initial[3]);
  
  at = string_at(&string, 5);
  assert.equal("String::stringAt at 5", at, initial[5]);

  string_destroy(&string);
};






inline void String::stringFind() {
  struct string string;
  char initial[] = "Hello World";
  string_init_initial(&string, initial);

  int at = string_find(&string, 'o');
  assert.equal("String::stringFind 'o'", at, 4);

  at = string_find(&string, 'k');
  assert.equal("String::stringFind 'k'", at, -1);

  string_destroy(&string);
};






inline void String::stringErase() {
  struct string string;
  char initial[] = "Hello World";
  char correct[] = "He World";

  string_init_initial(&string, initial);
  string_erase(&string, 2, 4);

  for(int i = 0; i < string.data.size; i++){
    char at = string_at(&string, i);
    assert.equal("String::stringErase iteration", at, correct[i]);
  };

  string_destroy(&string);
};






inline void String::stringSet() {
  struct string string;
  char initial[] = "Hello World";
  char correct[] = "Hbllo World";


  string_init_initial(&string, initial);

  string_set(&string, 'b', 1);

  char* ptr = string_get_ptr(&string);

  for(int i = 0; i < string.data.size; i++)
    assert.equal("String::stringGetPtr iteration", ptr[i], correct[i]);

  string_destroy(&string);
};






inline void String::stringGetPtr() {
  struct string string;
  char initial[] = "Hello World";

  string_init_initial(&string, initial);

  char* ptr = string_get_ptr(&string);

  for(int i = 0; i < string.data.size; i++)
    assert.equal("String::stringGetPtr iteration", ptr[i], initial[i]);

  string_destroy(&string);
};
};
