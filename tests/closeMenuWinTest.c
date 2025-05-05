#include <check.h>
#include <ncurses.h>

#include "../gui/cli/cli.h"

START_TEST(test_NULL) {
  closeMenuWin();
  ck_assert_ptr_null(getMenuWin());
}
END_TEST

START_TEST(not_NULL) {
  setMenuWin(newwin(10, 10, 0, 0));
  closeMenuWin();
  ck_assert_ptr_null(getMenuWin());
}
END_TEST

int closeMenuWinTest(void) {
  Suite *s = suite_create("closeMenuWinTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, test_NULL);
  tcase_add_test(tc_core, not_NULL);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
