#include "llist.c"
#include "llist.h"
#include "main.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>

int main(int argc, char *argv[]){
  if(validate_arguments(argc, argv)){
    printf("Arguments invalid\n");
  }else{
    printf("Arguments valid\n");
    argument_parser(argc, argv);
  }
  return 0;
}


int argument_parser(int argc, char *argv[]){
  char *arg = NULL;
  //int error_state = 0;
  struct node * head = NULL;
  struct node ** list_head = &head;


  for (int i = 1; i < argc; i++) {
    arg = argv[i];

    if(strcmp(arg, "ih") == 0){
      i++;
      char *str = argv[i];
      int value;
      if (validate_string_is_number(str, &value)){return 1;}
      insert_new_head(list_head, value);

    }else if(strcmp(arg, "it") == 0){
      i++;
      char *str = argv[i];
      int value;
      if (validate_string_is_number(str, &value)){return 1;}
      insert_new_tail(list_head, value);

    }else if(strcmp(arg, "dh") == 0){
      delete_head(list_head);

    }else if(strcmp(arg, "f") == 0){
      llist_free(list_head);

    }else if(strcmp(arg, "p") == 0){
      llist_print(*list_head);

    }else{
      return 1;
    }
  }
  return 0;
}

int validate_arguments(int argc, char *argv[]){
  char *arg = NULL;
  int error_state = 0;
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if((strcmp(arg, "ih") == 0) || (strcmp(arg, "it") == 0)){
      i++;
      int converted_string;
      if(validate_string_is_number(argv[i], &converted_string)){
        printf("number at %d is invalid\n", i);
        error_state = 1;
      }
      //else validate is valid
    }else if((strcmp(arg, "dh") == 0) || (strcmp(arg, "f") == 0) || (strcmp(arg, "p") == 0)){
      //valid
    }else{
      printf("argument %s at %d is invalid\n", argv[i], i);
      error_state = 1;
    }
  }
  return error_state;
}

int validate_string_is_number(char *str, int *result){
  //Return wether the input str is a valid number, and returns value through result
  char *end = NULL;

  errno = 0;

  long sl = strtol(str, &end, 10);

  //provided by: https://wiki.sei.cmu.edu/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number
  if (end == str) {
    (void) fprintf(stderr, "%s: not a decimal number\n", str);
  } else if ('\0' != *end) {
    (void) fprintf(stderr, "%s: extra characters at end of input: %s\n", str, end);
  } else if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno) {
    (void) fprintf(stderr, "%s out of range of type long\n", str);
  } else if (sl > INT_MAX) {
    (void) fprintf(stderr, "%ld greater than INT_MAX\n", sl);
  } else if (sl < INT_MIN) {
    (void) fprintf(stderr, "%ld less than INT_MIN\n", sl);
  } else{
    *result = sl;
    return 0;
  }
  return 1;

}

void insert_new_head(struct node **head, int value){
  //printf("insert_new_head, v: %d--\n", value);
  struct node *new_node = node_alloc(value);
  llist_insert_head(head, new_node);
  //printf("--\n");
}
void insert_new_tail(struct node **head, int value){
  //printf("insert_new_tail, v: %d--\n", value);
  struct node *new_node = node_alloc(value);
  llist_insert_tail(head, new_node);
  //printf("--\n");
}

void delete_head(struct node **head){
  struct node * old_head = llist_delete_head(head);
  if(old_head != NULL){
    node_free(old_head);
  }
}
