#ifndef PATHTESTS_H
#define PATHTESTS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "tests.h"
#include "../Structures/Path/path.h"

/* ===== Declarations ===== */

struct passed tests_path_run_all();

char tests_path_init();
char tests_path_init_initial();
char tests_path_init_initial_string();
char tests_path_destroy();
char tests_path_get_ptr();
char tests_path_set_string();
char tests_path_set();
char tests_path_cwd();
char tests_path_remove_last();
char tests_path_move();

/* ===== Test Runner ===== */

struct passed tests_path_run_all() {
  struct passed passed = {0};

  printf("==== Path Tests ====\n");

  if (tests_path_init()) passed.passed++;
  if (tests_path_init_initial()) passed.passed++;
  if (tests_path_init_initial_string()) passed.passed++;
  if (tests_path_destroy()) passed.passed++;
  if (tests_path_get_ptr()) passed.passed++;
  if (tests_path_set_string()) passed.passed++;
  if (tests_path_set()) passed.passed++;
  if (tests_path_cwd()) passed.passed++;
  if (tests_path_remove_last()) passed.passed++;
  if (tests_path_move()) passed.passed++;

  passed.all = 10;
  return passed;
}

/* ===== Tests ===== */

char tests_path_init() {
  struct path p;
  struct passed passed = {0};

  path_init(&p);

  if (strcmp(path_get_ptr(&p), "/") == 0) passed.passed++;
  else printf("path_init failed\n");

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_init_initial() {
  struct path p;
  struct passed passed = {0};

  path_init_initial(&p, "usr");


  if (strcmp(path_get_ptr(&p), "/usr/") == 0) passed.passed++;
  else printf("path_init_initial failed: %s != /usr/\n", path_get_ptr(&p));

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_init_initial_string() {
  struct path p;
  struct string s;
  struct passed passed = {0};

  string_init_initial(&s, "bin");
  path_init_initial_string(&p, &s);

  if (strcmp(path_get_ptr(&p), "/bin/") == 0) passed.passed++;
  else printf("path_init_initial_string failed\n");

  passed.all = 1;
  string_destroy(&s);
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_destroy() {
  struct path p;
  struct passed passed = {0};

  path_init(&p);
  path_destroy(&p);

  if (p.data.data.data == NULL) passed.passed++;
  else printf("path_destroy failed\n");

  passed.all = 1;
  return passed.passed == passed.all;
}

char tests_path_get_ptr() {
  struct path p;
  struct passed passed = {0};

  path_init_initial(&p, "etc");

  if (strcmp(path_get_ptr(&p), "/etc/") == 0) passed.passed++;
  else printf("path_get_ptr failed\n");

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_set_string() {
  struct path p;
  struct string s;
  struct passed passed = {0};

  path_init(&p);
  string_init_initial(&s, "home");

  path_set_string(&p, &s);

  if (strcmp(path_get_ptr(&p), "/home/") == 0) passed.passed++;
  else printf("path_set_string failed: %s != /home/\n", path_get_ptr(&p));

  passed.all = 1;
  string_destroy(&s);
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_set() {
  struct path p;
  struct passed passed = {0};

  path_init(&p);
  path_set(&p, "/tmp");

  if (strcmp(path_get_ptr(&p), "/tmp") == 0) passed.passed++;
  else printf("path_set failed\n");

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_cwd() {
  struct path p;
  struct passed passed = {0};

  path_init(&p);
  path_cwd(&p);

  char cwd[8192];
  getcwd(cwd, sizeof(cwd));
  cwd[strlen(cwd)] = '/';
  cwd[strlen(cwd)] = 0;

  if (strcmp(path_get_ptr(&p), cwd) == 0) passed.passed++;
  else printf("path_cwd failed: %s != %s\n", path_get_ptr(&p), cwd);

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
};

char tests_path_remove_last() {
  struct path p;
  struct passed passed = {0};

  path_init_initial(&p, "/usr/bin/");

  path_remove_last(&p);

  if (strcmp(path_get_ptr(&p), "/usr/") == 0) passed.passed++;
  else printf("path_remove_last failed: %s != /usr/\n", path_get_ptr(&p));

  passed.all = 1;
  path_destroy(&p);
  return passed.passed == passed.all;
}

char tests_path_move() {
  struct path p;
  struct string move;
  struct passed passed = {0};

  path_init_initial(&p, "/usr/bin/");
  string_init_initial(&move, "../lib/");

  path_move(&p, &move);

  if (strcmp(path_get_ptr(&p), "/usr/lib/") == 0) passed.passed++;
  else printf("path_move failed: %s != /usr/lib/\n", path_get_ptr(&p));

  passed.all = 1;
  path_destroy(&p);
  string_destroy(&move);
  return passed.passed == passed.all;
}

#endif
