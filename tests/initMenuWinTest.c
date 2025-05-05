#include <check.h>
#include <ncurses.h>

#include "../gui/cli/cli.h"

START_TEST(test_NULL) {
  int result = initMenuWin();
  ck_assert_int_eq(result, 0);
  ck_assert_ptr_ne(getMenuWin(), NULL);
}
END_TEST

START_TEST(not_NULL) {
  setMenuWin(newwin(10, 20, 0, 0));
  int result = initMenuWin();
  ck_assert_int_eq(result, 1);
  delwin(getMenuWin());
  setMenuWin(NULL);
}
END_TEST

int initMenuWinTest(void) {
  Suite *s = suite_create("initMenuWinTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, test_NULL);
  tcase_add_test(tc_core, not_NULL);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
