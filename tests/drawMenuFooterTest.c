#include <check.h>
#include <interface.h>

#include "../gui/cli/cli.h"

START_TEST(not_exit) {
  MenuItem_t current_item = Play;
  char buffer[6] = {0};
  startInterface();
  initMenuWin();
  drawMenuFooter(current_item);
  mvwinnstr(getMenuWin(), MENU_FOOTER_Y, INIT_MENU_ITEM_X, buffer, 5);
  endInterface();
  ck_assert_str_eq(buffer, "Exit ");
}
END_TEST

START_TEST(exit) {
  MenuItem_t current_item = Exit;
  char buffer[6] = {0};
  startInterface();
  initMenuWin();
  drawMenuFooter(current_item);
  //   int attr = getattrs(getMenuWin());
  mvwinnstr(getMenuWin(), MENU_FOOTER_Y, INIT_MENU_ITEM_X, buffer, 5);
  endInterface();
  ck_assert_str_eq(buffer, "Exit ");
  //   ck_assert_int_eq(attr & A_REVERSE, A_REVERSE);
}
END_TEST

int drawMenuFooterTest(void) {
  Suite *s = suite_create("drawMenuFooterTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, not_exit);
  tcase_add_test(tc_core, exit);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
