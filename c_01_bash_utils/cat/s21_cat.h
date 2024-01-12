#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  int n_flag;      // n 1
  int b_flag;      // b 2
  int e_flag;      // e 3
  int s_flag;      // s 4
  int t_flag;      // t 5
  int v_flag;      // v 6
  int false_flag;  // 7
  int no_flags;    // 8
} CatInfo;

void ParseArgs(CatInfo* info, char** argv, int argc);
void ParseShortArgs(CatInfo* info, char** argv, int i);
int CountFlags(char** argv, int argc, int* flags_amount);
void CheckEmptyLinesInRow(int buf, int* empty_lines);
void PrintFile(FILE* fp, CatInfo* info);

void PrintAll(int i, char* argv[], CatInfo* info);

#endif  // SRC_S21_CAT_H_
