#include <check.h>
#include <engine.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(valid) {
  setFieldCell(0, 0, 1);
  setFieldCell(1, 0, 2);
  setFieldCell(2, 0, 3);

  moveField(2, 0);

  ck_assert_int_eq(getFieldCell(0, 0), 0);
  ck_assert_int_eq(getFieldCell(1, 0), 1);
  ck_assert_int_eq(getFieldCell(2, 0), 2);
  setFieldCell(0, 0, 0);
  setFieldCell(1, 0, 0);
  setFieldCell(2, 0, 0);
}
END_TEST

START_TEST(edge_case) {
  setFieldCell(FIELD_HEIGHT - 1, 0, 1);
  setFieldCell(FIELD_HEIGHT - 2, 0, 2);

  moveField(FIELD_HEIGHT - 1, FIELD_HEIGHT - 2);

  ck_assert_int_eq(getFieldCell(FIELD_HEIGHT - 2, 0), 0);
  ck_assert_int_eq(getFieldCell(FIELD_HEIGHT - 1, 0), 2);
  setFieldCell(FIELD_HEIGHT - 1, 0, 0);
  setFieldCell(FIELD_HEIGHT - 2, 0, 0);
}
END_TEST

START_TEST(min_y_zero) {
  setFieldCell(0, 0, 1);
  setFieldCell(0, 1, 2);
  moveField(1, 0);
  ck_assert_int_eq(getFieldCell(0, 0), 0);
  ck_assert_int_eq(getFieldCell(1, 0), 1);
}
END_TEST

int moveFieldTest(void) {
  Suite *s = suite_create("moveFieldTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, valid);
  tcase_add_test(tc_core, edge_case);
  tcase_add_test(tc_core, min_y_zero);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
