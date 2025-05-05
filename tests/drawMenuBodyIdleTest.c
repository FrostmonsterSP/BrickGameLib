#include <check.h>

#include "../gui/cli/cli.h"

START_TEST(paused) {
  setMenuWin(newwin(10, 20, 0, 0));
  box(getMenuWin(), 0, 0);
  drawMenuBodyIdle(Play);
  char expected[] = "    Paused    ";
  char actual[15];
  mvwinnstr(getMenuWin(), 1, 1, actual, 14);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(test_continue) {
  setMenuWin(newwin(10, 20, 0, 0));
  box(getMenuWin(), 0, 0);
  drawMenuBodyIdle(Play);
  char expected[] = " Continue ";
  char actual[11] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y, IDLE_MENU_ITEM_X, actual, 10);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(restart) {
  setMenuWin(newwin(10, 20, 0, 0));
  box(getMenuWin(), 0, 0);
  drawMenuBodyIdle(LevelRestart);
  char expected[] = " Restart ";
  char actual[10] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, IDLE_MENU_ITEM_X, actual, 9);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected, actual);
}
END_TEST

int drawMenuBodyIdleTest(void) {
  Suite *s = suite_create("drawMenuBodyIdleTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, paused);
  tcase_add_test(tc_core, test_continue);
  tcase_add_test(tc_core, restart);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
