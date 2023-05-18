#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **ext_var;

int _putchar(char c);
int beautsh(const char *a, unsigned int b);
int _args(char *c, char **args);
int execute(char **c);
void _free(char **d, int e);
void _verfree(char *c);
int com_exist(char *path);
int _verth(char **args);
int _verpth(char **args, int i);
int not_exist(char **args, int m);
void _cdir(char *dir);

#endif
