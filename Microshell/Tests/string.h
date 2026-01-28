#ifndef STRINGTESTS_H
#define STRINGTESTS_H

#include <stdio.h>
#include <string.h>
#include "tests.h"
#include "../Structures/String/string.h"

/* ===== Declarations ===== */

struct passed tests_string_run_all();

char tests_string_init();
char tests_string_init_initial();
char tests_string_init_initial_string();
char tests_string_destroy();
char tests_string_get_set();
char tests_string_concat();
char tests_string_concat_string();
char tests_string_find();
char tests_string_erase();
char tests_string_get_ptr();

/* ===== Test Runner ===== */

struct passed tests_string_run_all() {
  struct passed passed = {0};

  printf("==== String Tests ====\n");

  if (tests_string_init()) passed.passed++;
  if (tests_string_init_initial()) passed.passed++;
  if (tests_string_init_initial_string()) passed.passed++;
  if (tests_string_destroy()) passed.passed++;
  if (tests_string_get_set()) passed.passed++;
  if (tests_string_concat()) passed.passed++;
  if (tests_string_concat_string()) passed.passed++;
  if (tests_string_find()) passed.passed++;
  if (tests_string_erase()) passed.passed++;
  if (tests_string_get_ptr()) passed.passed++;

  passed.all = 10;
  return passed;
}

/* ===== Tests ===== */

char tests_string_init() {
  struct string s;
  struct passed passed = {0};

  string_init(&s);

  if (s.data.size == 1) passed.passed++;
  else printf("string_init size failed\n");

  char c = string_get(&s, 0);
  if (c == '\0') passed.passed++;
  else printf("string_init null terminator failed\n");

  passed.all = 2;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_init_initial() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "abc");

  if (s.data.size == 4) passed.passed++;
  else printf("init_initial size failed\n");

  if (string_get(&s, 1) == 'b') passed.passed++;
  else printf("init_initial data failed\n");

  passed.all = 2;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_init_initial_string() {
  struct string a, b;
  struct passed passed = {0};

  string_init_initial(&a, "hello");
  string_init_initial_string(&b, &a);

  if (b.data.size == a.data.size) passed.passed++;
  else printf("init_initial_string size failed: %d = %d\n", b.data.size, a.data.size);

  if (string_get(&b, 4) == 'o') passed.passed++;
  else printf("init_initial_string data failed: %s\n", string_get(&b, 4));

  passed.all = 2;
  string_destroy(&a);
  string_destroy(&b);
  return passed.passed == passed.all;
}

char tests_string_destroy() {
  struct string s;
  struct passed passed = {0};

  string_init(&s);
  string_destroy(&s);

  if (s.data.data == NULL) passed.passed++;
  else printf("string_destroy failed\n");

  passed.all = 1;
  return passed.passed == passed.all;
}

char tests_string_get_set() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "abc");

  string_set(&s, 'z', 1);

  if (string_get(&s, 1) == 'z') passed.passed++;
  else printf("string_set/get failed\n");

  passed.all = 1;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_concat() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "foo");
  string_concat(&s, "bar");

  if (string_find(&s, "foobar") == 0) passed.passed++;
  else printf("string_concat failed\n");

  passed.all = 1;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_concat_string() {
  struct string a, b;
  struct passed passed = {0};

  string_init_initial(&a, "foo");
  string_init_initial(&b, "bar");

  string_concat_string(&a, &b);

  if (string_find(&a, "foobar") == 0) passed.passed++;
  else printf("string_concat_string failed\n");

  passed.all = 1;
  string_destroy(&a);
  string_destroy(&b);
  return passed.passed == passed.all;
}

char tests_string_find() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "hello world");

  if (string_find(&s, "world") == 6) passed.passed++;
  else printf("string_find failed\n");

  passed.all = 1;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_erase() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "abcdef");

  string_erase(&s, 1, 3); /* remove bcd */

  if (string_find(&s, "aef") == 0) passed.passed++;
  else printf("string_erase failed\n");

  passed.all = 1;
  string_destroy(&s);
  return passed.passed == passed.all;
}

char tests_string_get_ptr() {
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "test");

  const char* p = string_get_ptr(&s);

  if (strcmp(p, "test") == 0) passed.passed++;
  else printf("string_get_ptr failed\n");

  passed.all = 1;
  string_destroy(&s);
  return passed.passed == passed.all;
}

#endif
