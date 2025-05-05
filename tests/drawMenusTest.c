#include <check.h>
#include <interface.h>

#include "../gui/cli/cli.h"
#include "engine.h"

START_TEST(InitState) {
  startInterface();
  initMenuWin();
  drawMenus(StateInit, Play);
  char expected[] = "Level ";
  char actual[7] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, INIT_MENU_ITEM_X, actual, 6);
  closeMenuWin();
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(IdleState) {
  startInterface();
  initMenuWin();
  drawMenus(StateIdle, Play);
  char expected[] = " Restart  ";
  char actual[11] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, IDLE_MENU_ITEM_X, actual, 10);
  closeMenuWin();
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

int drawMenusTest(void) {
  Suite *s = suite_create("drawMenusTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, InitState);
  tcase_add_test(tc_core, IdleState);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
