#ifndef MAIN_H
#define MAIN_H

//int main(int argc, char *argv[]);

int validate_arguments(int argc, char *argv[]);

int argument_parser(int argc, char *argv[]);

int validate_string_is_number(char *str, int *result);
void insert_new_head(struct node **head, int value);
void insert_new_tail(struct node **head, int value);
void delete_head(struct node **head);

#endif
