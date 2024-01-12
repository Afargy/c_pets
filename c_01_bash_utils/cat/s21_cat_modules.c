#include "s21_cat.h"

void PrintNoArgs() {
  char buf[4096];
  int bytes_read;

  bytes_read = scanf("%c", buf);

  while (bytes_read > 0) {
    printf("%.*s", bytes_read, buf);
    bytes_read = scanf("%c", buf);
  }
}

void ParseArgs(CatInfo* info, char** argv, int argc) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        info->b_flag = 1;
      } else if (strcmp(argv[i], "--number") == 0) {
        info->n_flag = 1;
      } else if (strcmp(argv[i], "--s_flag-blank") == 0) {
        info->s_flag = 1;
      } else {
        info->false_flag = 1;
      }
    } else if (argv[i][0] == '-' && argv[i][1] != '-' && argv[i][1]) {
      ParseShortArgs(info, argv, i);
    } else {
      break;
    }
  }

  if (!info->n_flag && !info->b_flag && !info->e_flag && !info->s_flag &&
      !info->t_flag && !info->v_flag && !info->false_flag)
    info->no_flags = 1;

  if (info->n_flag && info->b_flag) info->n_flag = 0;

  if (info->false_flag) {
    info->n_flag = 0;
    info->b_flag = 0;
    info->e_flag = 0;
    info->s_flag = 0;
    info->t_flag = 0;
    info->v_flag = 0;
    info->no_flags = 0;
  }
}

void ParseShortArgs(CatInfo* info, char** argv, int i) {
  int flag = 1;
  for (int j = 1; flag == 1; j++) {
    if (argv[i][j] == 'n')
      info->n_flag = 1;
    else if (argv[i][j] == 'b')
      info->b_flag = 1;
    else if (argv[i][j] == 'e') {
      info->e_flag = 1;
      info->v_flag = 1;
    } else if (argv[i][j] == 's')
      info->s_flag = 1;
    else if (argv[i][j] == 't') {
      info->t_flag = 1;
      info->v_flag = 1;
    } else if (argv[i][j] == 'v')
      info->v_flag = 1;
    else if (argv[i][j] == 'E')
      info->e_flag = 1;
    else if (argv[i][j] == 'T')
      info->t_flag = 1;
    else if (argv[i][j] == '\0')
      flag = 0;
    else
      info->false_flag = 1;
  }
}

int CountFlags(char** argv, int argc, int* flags_amount) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      (*flags_amount)++;
    } else {
      break;
    }
  }
  return *flags_amount;
}

void CheckEmptyLinesInRow(int buf, int* empty_lines) {
  if (buf == '\n')
    (*empty_lines)++;
  else
    (*empty_lines) = 0;
}

void PrintAll(int i, char* argv[], CatInfo* info) {
  FILE* fp = fopen(argv[i], "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
  } else {
    PrintFile(fp, info);
    fclose(fp);
    fp = NULL;
  }
}

void PrintFile(FILE* fp, CatInfo* info) {
  int buf, empty_lines = 0, pre_elem = 32, line = 1;
  while ((buf = fgetc(fp)) != EOF) {
    int flag = 1;
    if (info->s_flag) CheckEmptyLinesInRow(buf, &empty_lines);
    if ((info->s_flag) && (empty_lines > 2)) flag = 0;
    if ((flag && info->s_flag) || !info->s_flag) {
      if ((info->b_flag)) {
        if (((buf != '\n') && (info->b_flag) && (line == 1)) ||
            ((buf != '\n') && (info->b_flag) && (pre_elem == '\n')))
          printf("%6d\t", line++);
      }
      if ((info->n_flag)) {
        if (((line == 1) && (info->n_flag)) ||
            ((pre_elem == '\n') && (info->n_flag))) {
          printf("%6d\t", line++);
        }
      }
      if ((buf == '\t') && (info->t_flag)) {
        printf("^");
        buf = 'I';
      }
      if ((buf == '\n') && (info->e_flag)) printf("$");
      if ((info->v_flag) && (buf != '\n') && (buf != '\t')) {
        if (((buf >= 0) && (buf < 9)) || ((buf > 10) && (buf < 32)) ||
            ((buf > 126) && (buf <= 160))) {
          printf("^");
          if (buf > 126) {
            buf = buf - 64;
          } else {
            buf = buf + 64;
          }
        }
      }
      printf("%c", buf);
      pre_elem = buf;
    }
  }
}
