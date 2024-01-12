#ifndef SRC_S21_GREP_H
#define SRC_S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool e_flag;
  bool i_flag;
  bool v_flag;
  bool c_flag;
  bool l_flag;
  bool n_flag;
  bool h_flag;
  bool s_flag;
  bool f_flag;
  bool o_flag;
  bool zero_pattern;
  bool wrong_flag;
  bool wrong_path;
} GrepFlags;

void OpenWithF(char* patterns, int* pattern_counter, char* optarg,
               GrepFlags* flags);

void AddPattern(char* patterns, int* pattern_counter, char* new_pat);
GrepFlags ParseFlags(int argc, char** argv, char* patterns);
void PrintFlags(GrepFlags options);
void OpenFile(int argc, char** argv, GrepFlags* flags, char* patterns);
void GrepFiles(FILE* fp, GrepFlags* flags, char* patterns, char** argv,
               int files_amount);
void CountPaths(int argc, char** argv, int* path_counter);
void PrintWithLC(GrepFlags* flags, int matched_lines, int files_amount,
                 char** argv);
void PrintFile(GrepFlags* flags, char** argv, int line_counter,
               int files_amount, char* buf, regex_t my_regex);

#endif  // SRC_S21_GREP_H
