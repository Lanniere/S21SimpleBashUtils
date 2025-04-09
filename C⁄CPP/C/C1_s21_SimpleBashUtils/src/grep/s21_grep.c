#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc < 2) return 1;

  flags flags = {0};
  if (parser(argc, argv, &flags) == true) readFile(argc, argv, &flags);
}

bool parser(int argc, char **argv, flags *flags) {
  int opt;
  bool result = true;
  opterr = 0;
  while ((opt = getopt(argc, argv, "e:ivclnf:hs")) != -1 && result == true) {
    switch (opt) {
      case 'e':
        flags->e = true;
        patterns(flags, optarg);
        break;
      case 'i':
        flags->i = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'c':
        flags->c = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'f':
        flags->f = true;
        flag_f(flags, optarg);
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      default:
        if (flags->s == false)
          fprintf(stderr, "grep: invalid option -- '%c'\n", opt);
        result = false;
        break;
    }
  }
  if (result == true) {
    if (flags->l == true) flags->c = false;

    if (flags->e == 0 && flags->f == 0) {
      patterns(flags, argv[optind]);
      optind++;
    }
    if (argc - optind > 1 && flags->h == false)
      flags->many_files = true;
    else
      flags->many_files = false;
  }
  return result;
}

void patterns(flags *flags, char *new_pattern) {
  if (new_pattern == NULL) return;

  if (flags->patterns == NULL) {
    flags->patterns = calloc(strlen(new_pattern) + 1, sizeof(char));
    strcpy(flags->patterns, new_pattern);
  } else {
    char *tmp = realloc(flags->patterns,
                        strlen(flags->patterns) + strlen(new_pattern) + 2);
    if (tmp == NULL) {
      fprintf(stderr, "Error allocation memory.");
    } else {
      flags->patterns = tmp;
      strcat(flags->patterns, "|");
      strcat(flags->patterns, new_pattern);
    }
  }
}
void flag_f(flags *flags, char *filename) {
  char *line = NULL;
  size_t c = 0;
  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Error opening file.\n");
  } else {
    while ((getline(&line, &c, fp)) != -1) patterns(flags, line);
    fclose(fp);
  }

  if (line != NULL) free(line);
}

void readFile(int argc, char **argv, flags *flags) {
  if (flags->patterns == NULL) return;

  regex_t regular;
  if (regcomp(&regular, flags->patterns,
              (flags->i) ? REG_ICASE : REG_EXTENDED) == 0) {
    for (; optind < argc; optind++) {
      FILE *fp = fopen(argv[optind], "r");
      if (fp == NULL) {
        if (flags->s == false) fprintf(stderr, "Error opening file.\n");
        continue;
      }
      work(argv, flags, fp, &regular);
      fclose(fp);
    }

    regfree(&regular);
  }
  free(flags->patterns);
}

void work(char **argv, flags *flags, FILE *fp, regex_t *regular) {
  char *line = NULL;
  int num_line = 1;
  size_t c = 0;
  size_t match = 0;
  regmatch_t end = {0};
  int count = 0;
  while ((getline(&line, &c, fp)) != -1) {
    if (regexec(regular, line, match, &end, REG_NOTEOL) == 0) {
      count++;
      print_line(flags, line, argv, num_line);
    } else if (flags->v == true) {
      print_line(flags, line, argv, num_line);
    }
    num_line++;
  }
  if (flags->l == true && count != 0) printf("%s\n", argv[optind]);
  if (flags->c == true) {
    if (flags->many_files == true) printf("%s:", argv[optind]);
    if (flags->v)
      printf("%d\n", num_line - count - 1);
    else
      printf("%d\n", count);
  }

  free(line);
}

void print_line(flags *flags, char *line, char **argv, int num_line) {
  if (flags->c == false && flags->l == false) {
    if (flags->many_files == true) printf("%s:", argv[optind]);
    if (flags->n == true) printf("%d:", num_line);
    printf("%s", line);
  }
}
