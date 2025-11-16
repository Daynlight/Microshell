#pragma once 
#include "Assert.h"


namespace Structures::UnitTests{
class String{
private:
  Tests::Assert assert;
public:
  bool runAll();
  
  void stringInit();
  void stringDestroy();

  void stringConcat();
  void stringAt();
  void stringFind();
  void stringErase();
  void stringGetPtr();
};











inline bool String::runAll(){
  printf("==== String Tests ====\n");

  stringInit();
  stringDestroy();
  stringConcat();
  stringAt();
  stringFind();
  stringErase();
  stringGetPtr();

  return assert.results("String");
};






inline void String::stringInit() {
  struct string string;
  char initial[] = "Hello World";
  string_init(&string, initial);

  assert.isNotNullptr("String::stringInit data", (const char*)&string.data);

  for(int i = 0; i < string.data.size; i++){
    char at = string_at(&string, i);
    assert.equal("String::stringInit iteration", at, initial[i]);
  }

  string_destroy(&string);
};






inline void String::stringDestroy() {
  struct string string;
  char initial[] = "Hello World";
  string_init(&string, initial);
  string_destroy(&string);

  assert.isNullptr("String::stringDestroy data", (const char*)&string.data);
};






inline void String::stringConcat() {
  struct string string;
  char initial[] = "Hello ";
  struct string string2;
  char initial2[] = "World";
  char complete[] = "Hello World";
  
  string_init(&string, initial);
  string_init(&string2, initial2);
  string_concat(&string, &string2);

  assert.isNotNullptr("String::stringConcat data", (const char*)&string.data);

  for(int i = 0; i < string.data.size; i++){
    char at = string_at(&string, i);
    assert.equal("String::stringConcat iteration", at, complete[i]);
  };

  string_destroy(&string);
};






inline void String::stringAt() {
};






inline void String::stringFind() {
};






inline void String::stringErase() {
};






inline void String::stringGetPtr() {
};
};
