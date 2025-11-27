#ifndef STRINGEXAMPLE
#define STRINGEXAMPLE


void string_concat_example(){
  printf("== Concat Example ==\n");

  struct string string;
  char initial[] = "Hello ";
  char initial2[] = "World";
  
  string_init_initial(&string, initial);

  string_concat(&string, initial2);

  printf("%s\n", string_get_ptr(&string));

  string_destroy(&string);
}



#endif



