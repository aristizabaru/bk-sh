#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/errno.h>

/*shell*/
void shell_loop(int *, int *, char *, char **,
                size_t *, int *, char ***, char ***, char **);

/*auxfunctions_1*/
char *_strcat(char *, char *);
void _strcpy(char *, char *);
int _strlen(char *);
int wrdcounter(char *);
int _atoi(char *);

/*auxfunctions_2*/
void free_arguments(char ***, char **);
void create_memstrings(char **, char **, int);
void copybytes_memstrings(char **, char **, int);
void splitter(char **, char ***, int);
int get_arguments(char **, char ***);

/*auxfunctions_3*/
void run_command(char ***, int, char **, char **);
int find_path(char ***, char **);
void create_paths(char *, char ***);
void recursion_fill_path(char *, char ***, int, int);
int compare_paths(char ***, char ***);

/*auxfunctions_4*/
void create_nonInterac_arg_array(int, char **, char ***);
void sigint_handler(int);
int check_file(char *);
void push_char(char **, char);
void notfoundfunc(char **, int, char **);

/*auxfunctions_5*/
void check_exit_compare(char *, int *, int *);
int check_exit(char *);
void check_error(int);
void printnum(int);
void exit_illegal_command(char *, int, char *);

/*auxfuntions_6*/
void envprint(char **);
int stringcomp(char *, char *);
void recursion_fill_arg_array(char *, char ***, int, int);

#endif
