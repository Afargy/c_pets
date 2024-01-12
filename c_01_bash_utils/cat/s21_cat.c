#include "s21_cat.h"

int main(int argc, char** argv) {
  CatInfo info = {0, 0, 0, 0, 0, 0, 0, 0};
  ParseArgs(&info, argv, argc);

  int flags_amount = 1;
  CountFlags(argv, argc, &flags_amount);
  if (!info.false_flag) {
    for (int i = flags_amount; i < argc; i++) {
      PrintAll(i, argv, &info);
    }
  } else {
    fprintf(stderr, "cat: illegal options read --help\n");
  }
  return 0;
}
