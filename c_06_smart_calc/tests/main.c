#include <math.h>

#include "test.h"

int main() {
  SRunner *sr = srunner_create(suite_1());
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}
