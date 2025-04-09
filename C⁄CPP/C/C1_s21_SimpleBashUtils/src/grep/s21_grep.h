#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool i;
  bool c;
  bool l;
  bool n;
  bool e;
  bool v;
  bool f;
  bool h;
  bool s;
  char *patterns;
  bool many_files;
} flags;

bool parser(int argc, char **argv, flags *flags);
void flag_f(flags *flags, char *filename);
void patterns(flags *flags, char *pattern);
void work(char **argv, flags *flags, FILE *fp, regex_t *regular);
void readFile(int argc, char **argv, flags *flags);
void print_line(flags *flags, char *line, char **argv, int num_line);
