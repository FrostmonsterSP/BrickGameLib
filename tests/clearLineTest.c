#include <check.h>
#include <engine.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(begin) {
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, x, 1);
  }
  clearLine(0);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(getFieldCell(0, x), 0);
  }
}
END_TEST

START_TEST(middle) {
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, FIELD_HEIGHT / 2, 1);
  }
  clearLine(FIELD_HEIGHT / 2);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(getFieldCell(FIELD_HEIGHT / 2, x), 0);
  }
}
END_TEST

START_TEST(end) {
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(FIELD_HEIGHT - 1, x, 1);
  }
  clearLine(FIELD_HEIGHT - 1);
  for (int x = 0; x < FIELD_WIDTH; x++) {
    ck_assert_int_eq(getFieldCell(FIELD_HEIGHT - 1, x), 0);
  }
}
END_TEST

int clearLineTest(void) {
  Suite *s = suite_create("clearLineTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, begin);
  tcase_add_test(tc_core, middle);
  tcase_add_test(tc_core, end);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
