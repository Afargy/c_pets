#include "../3d_viewer.h"
#include "check.h"

// void showObj(obj_t obj);
// void showVer(obj_t obj);
// void showPol(obj_t obj);

// int main(void) {
//   // Suite *s = suite_create("Core");
//   // TCase *tc = tcase_create("Core");
//   // tcase_add_test(tc, test1);
//   // tcase_add_test(tc, test2);
//   // tcase_add_test(tc, test3);
//   // tcase_add_test(tc, test4);
//   // tcase_add_test(tc, test5);
//   // tcase_add_test(tc, test6);
//   // tcase_add_test(tc, test7);
//   // tcase_add_test(tc, test8);
//   // tcase_add_loop_test(tc, test1, 0, 31);

//   // SRunner *sr = srunner_create(s);
//   // suite_add_tcase(s, tc);

//   // srunner_run_all(sr, CK_ENV);
//   // srunner_ntests_failed(sr);
//   // srunner_free(sr);

//   obj_t obj = {0, 0, 0, NULL, NULL, 0};
//   // char *n =
//   // "/home/babaka/Desktop/1234/C8_3DViewer_v1.0-1/src/tests/cube.obj";
//   char *n = "/Users/clockbel/goinfre/City2.obj";

//   int err = parseFile(n, &obj);
//   showObj(obj);

//   return (0);
// }

// void showVer(obj_t obj) {
//   for (unsigned i = 0; i < obj.vertsNum; i++) {
//     size_t cur = i * 3;
//     printf("%u: %lf %lf %lf\n", i + 1, obj.verts[cur], obj.verts[cur + 1],
//            obj.verts[cur + 2]);
//   }
// }

// void showPol(obj_t obj) {
//   for (size_t i = 0; i < obj.dotsNum * 2; i++) {
//     printf("%u ", obj.facets[i]);
//   }
//   printf("\n");
// }

// void showObj(obj_t obj) {
//   printf("\n");
//   showVer(obj);
//   printf("Poligons:%d\n", obj.dotsNum);
//   printf("F:%d\n", obj.facetsNum);
//   printf("V:%d\n", obj.vertsNum);
//   // showPol(obj);
// }

START_TEST(test1) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.000000, -1.000000, -1.000000, -1.000000, 1.000000,
                      -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,
                      -1.000000, -1.000000, -1.000000, -1.000000, 1.000000,
                      -1.000000, 1.000000,  1.000000,  1.000000,  1.000000,
                      1.000000,  1.000000,  -1.000000, 1.000000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test2) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {0.000000,  -1.000000, -1.000000, 0.000000,  1.000000,
                      -1.000000, 2.000000,  1.000000,  -1.000000, 2.000000,
                      -1.000000, -1.000000, 0.000000,  -1.000000, 1.000000,
                      0.000000,  1.000000,  1.000000,  2.000000,  1.000000,
                      1.000000,  2.000000,  -1.000000, 1.000000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  moveX(&obj, 1);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test3) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.000000, 0.000000,  -1.000000, -1.000000, 2.000000,
                      -1.000000, 1.000000,  2.000000,  -1.000000, 1.000000,
                      0.000000,  -1.000000, -1.000000, 0.000000,  1.000000,
                      -1.000000, 2.000000,  1.000000,  1.000000,  2.000000,
                      1.000000,  1.000000,  0.000000,  1.000000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  moveY(&obj, 1);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test4) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.000000, -1.000000, 0.000000,  -1.000000, 1.000000,
                      0.000000,  1.000000,  1.000000,  0.000000,  1.000000,
                      -1.000000, 0.000000,  -1.000000, -1.000000, 2.000000,
                      -1.000000, 1.000000,  2.000000,  1.000000,  1.000000,
                      2.000000,  1.000000,  -1.000000, 2.000000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  moveZ(&obj, 1);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test5) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.000000, -0.964491, -1.034290, -1.000000, 1.034290,
                      -0.964491, 1.000000,  1.034290,  -0.964491, 1.000000,
                      -0.964491, -1.034290, -1.000000, -1.034290, 0.964491,
                      -1.000000, 0.964491,  1.034290,  1.000000,  0.964491,
                      1.034290,  1.000000,  -1.034290, 0.964491};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  rotateX(&obj, 2);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test6) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.034290, -1.000000, -0.964491, -1.034290, 1.000000,
                      -0.964491, 0.964491,  1.000000,  -1.034290, 0.964491,
                      -1.000000, -1.034290, -0.964491, -1.000000, 1.034290,
                      -0.964491, 1.000000,  1.034290,  1.034290,  1.000000,
                      0.964491,  1.034290,  -1.000000, 0.964491};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  rotateY(&obj, 2);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test7) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-0.964491, -1.034290, -1.000000, -1.034290, 0.964491,
                      -1.000000, 0.964491,  1.034290,  -1.000000, 1.034290,
                      -0.964491, -1.000000, -0.964491, -1.034290, 1.000000,
                      -1.034290, 0.964491,  1.000000,  0.964491,  1.034290,
                      1.000000,  1.034290,  -0.964491, 1.000000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  rotateZ(&obj, 2);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

START_TEST(test8) {
  obj_t obj = {0, 0, 0, NULL, NULL, 0};
  int dots[48] = {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 1, 5, 5, 4, 4, 0,
                  0, 4, 4, 7, 7, 3, 3, 0, 6, 7, 7, 4, 4, 5, 5, 6,
                  6, 5, 5, 1, 1, 2, 2, 6, 6, 2, 2, 3, 3, 7, 7, 6};
  double verts[24] = {-1.340000, -1.340000, -1.340000, -1.340000, 1.340000,
                      -1.340000, 1.340000,  1.340000,  -1.340000, 1.340000,
                      -1.340000, -1.340000, -1.340000, -1.340000, 1.340000,
                      -1.340000, 1.340000,  1.340000,  1.340000,  1.340000,
                      1.340000,  1.340000,  -1.340000, 1.340000};
  obj_t res = {8, 6, 24, verts, dots, 0};
  parseFile("tests/cube.obj", &obj);
  scale(&obj, 1.34);

  for (int i = 0; i < obj.dotsNum * 2; i++) {
    ck_assert_int_eq(obj.facets[i], res.facets[i]);
    if (i < obj.dotsNum) {
      ck_assert_double_eq_tol(obj.verts[i], res.verts[i], 1e-6);
    }
  }

  ck_assert_int_eq(obj.vertsNum, res.vertsNum);
  ck_assert_int_eq(obj.facetsNum, res.facetsNum);
  ck_assert_int_eq(obj.dotsNum, res.dotsNum);
  freeObject(&obj);
}
END_TEST

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  tcase_add_loop_test(tc, test1, 0, 31);

  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);
  return (0);
}
