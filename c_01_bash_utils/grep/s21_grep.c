#include "s21_grep.h"

void AddPattern(char* patterns, int* pattern_counter, char* new_pat) {
  if (*pattern_counter != 0) {
    strcat(patterns, "|");
  }
  strcat(patterns, new_pat);
  (*pattern_counter)++;
  return;
}

GrepFlags ParseFlags(int argc, char** argv, char* patterns) {
  GrepFlags flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int cur_flag = 0;
  int pattern_counter = 0;
  while ((cur_flag = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) !=
         -1) {
    switch (cur_flag) {
      case 'e':
        flags.e_flag = 1;
        if (*optarg == 0 || *optarg == ' ') flags.zero_pattern = 1;
        if (!flags.zero_pattern) AddPattern(patterns, &pattern_counter, optarg);
        break;
      case 'i':
        flags.i_flag = 1;
        break;
      case 'v':
        flags.v_flag = 1;
        break;
      case 'c':
        flags.c_flag = 1;
        break;
      case 'l':
        flags.l_flag = 1;
        break;
      case 'n':
        flags.n_flag = 1;
        break;
      case 'h':
        flags.h_flag = 1;
        break;
      case 's':
        flags.s_flag = 1;
        break;
      case 'f':
        flags.f_flag = 1;
        OpenWithF(patterns, &pattern_counter, optarg, &flags);
        break;
      case 'o':
        flags.o_flag = 1;
        break;
      case '?':
        flags.wrong_flag = 1;
        break;
      default:
        break;
    }
  }
  return flags;
}

void OpenWithF(char* patterns, int* pattern_counter, char* optarg,
               GrepFlags* flags) {
  FILE* fp = NULL;
  if ((fp = fopen(optarg, "r")) != NULL) {
    char str[4096] = {'\0'};
    while (feof(fp) == 0) {
      fgets(str, 4095, fp);
      if (str[0] == '\n') {
        flags->zero_pattern = 1;
      }
      if (!flags->zero_pattern) {
        int len = (strlen(str));
        if (str[len - 1] == '\n') {
          str[len - 1] = '\0';
        } else if (str[len - 1] != '\n') {
          len++;
        }
        char new_str[len];
        for (int i = 0; i < len; i++) {
          new_str[i] = str[i];
        }
        AddPattern(patterns, pattern_counter, new_str);
        if (patterns[strlen(patterns) - 1] == '|' &&
            str[strlen(str) - 1] != '|') {
          patterns[strlen(patterns) - 1] = '\0';
        }
        str[0] = '\0';
      }
    }

  } else {
    flags->wrong_path = 1;
  }

  fclose(fp);
}

void PrintFlags(GrepFlags options) {
  printf("e_flag = %d\n", options.e_flag);
  printf("i_flag = %d\n", options.i_flag);
  printf("v_flag = %d\n", options.v_flag);
  printf("c_flag = %d\n", options.c_flag);
  printf("l_flag = %d\n", options.l_flag);
  printf("n_flag = %d\n", options.n_flag);
  printf("h_flag = %d\n", options.h_flag);
  printf("s_flag = %d\n", options.s_flag);
  printf("f_flag = %d\n", options.f_flag);
  printf("o_flag = %d\n", options.o_flag);
  printf("printall = %d\n", options.zero_pattern);
  printf("wrong flags = %d\n", options.wrong_flag);
  printf("wrong path = %d\n", options.wrong_path);
  printf("\n");
}

void PrintWithLC(GrepFlags* flags, int matched_lines, int files_amount,
                 char** argv) {
  if (flags->c_flag && !flags->l_flag && files_amount == 1)
    printf("%d\n", matched_lines);
  else if (flags->c_flag && !flags->l_flag && files_amount > 1)
    printf("%s:%d\n", argv[optind], matched_lines);

  if (flags->l_flag) {
    if (matched_lines > 0 && !flags->c_flag) {
      printf("%s\n", argv[optind]);
    }
    if (flags->c_flag && matched_lines > 0 && files_amount > 1)
      printf("%s:1\n%s\n", argv[optind], argv[optind]);
    else if (flags->c_flag && matched_lines == 0 && files_amount > 1)
      printf("%s:0\n", argv[optind]);
    else if (flags->c_flag && matched_lines > 0)
      printf("1\n%s\n", argv[optind]);
    else if (flags->c_flag && matched_lines == 0)
      printf("0\n");
  }
}

void OpenFile(int argc, char** argv, GrepFlags* flags, char* patterns) {
  int files_amount = argc - optind;
  if (!flags->e_flag && !flags->f_flag) files_amount--;
  if (!flags->e_flag && !flags->f_flag) {
    strcat(patterns, argv[optind]);
    optind++;
  }
  for (int i = optind; optind < argc; i++) {
    FILE* fp = fopen(argv[i], "r");
    if (fp == NULL) {
      if (!flags->s_flag)
        fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                argv[optind]);
    } else {
      GrepFiles(fp, flags, patterns, argv, files_amount);
      fclose(fp);
      fp = NULL;
    }
    optind++;
  }
}

void PrintWithO(regex_t my_regex, char* str) {
  regmatch_t match = {0};
  int enter = 0;
  while (regexec(&my_regex, str + enter, 1, &match, 0) == 0) {
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      printf("%c", str[i + enter]);
    }
    printf("\n");
    enter += match.rm_eo;
  }
}

void PrintFile(GrepFlags* flags, char** argv, int line_counter,
               int files_amount, char* buf, regex_t my_regex) {
  if (!flags->c_flag && !flags->l_flag)
    if (files_amount > 1 && !flags->h_flag && files_amount > 1)
      printf("%s:", argv[optind]);
  if (!flags->c_flag && !flags->l_flag) {
    if (flags->n_flag) printf("%d:", line_counter);
    if (!flags->o_flag || (flags->o_flag && flags->v_flag))
      printf("%s", buf);
    else
      PrintWithO(my_regex, buf);
    if ((buf[strlen(buf) - 1] != '\n' && !flags->o_flag) ||
        (flags->o_flag && flags->v_flag && buf[strlen(buf) - 1] != '\n'))
      printf("\n");
  }
}

void GrepFiles(FILE* fp, GrepFlags* flags, char* patterns, char** argv,
               int files_amount) {
  regex_t my_regex;
  char buf[4096];
  int line_counter = 0;
  int matched_lines = 0;
  while (feof(fp) == 0) {
    line_counter++;

    if (!flags->i_flag)
      regcomp(&my_regex, patterns, REG_EXTENDED | REG_NEWLINE);
    else if (flags->i_flag)
      regcomp(&my_regex, patterns, REG_ICASE | REG_EXTENDED | REG_NEWLINE);

    if (fgets(buf, 4096, fp)) {
      int match = 0;

      if (flags->v_flag)
        match = regexec(&my_regex, buf, 0, 0, 0);
      else
        match = !regexec(&my_regex, buf, 0, 0, 0);

      if (flags->zero_pattern) {
        match = 1;
      }

      if (match) {
        matched_lines++;
        PrintFile(flags, argv, line_counter, files_amount, buf, my_regex);
      }
    }
    regfree(&my_regex);
  }
  PrintWithLC(flags, matched_lines, files_amount, argv);
}

int main(int argc, char** argv) {
  char patterns[4096] = {0};
  GrepFlags flags = ParseFlags(argc, argv, patterns);
  if (argc > 1)
    if (!flags.wrong_flag) OpenFile(argc, argv, &flags, patterns);
  return 0;
}
