#include <check.h>
#include <interface.h>
#include <ncurses.h>

#include "../gui/cli/cli.h"

START_TEST(all_windows) {
  WINDOW *menu = newwin(10, 10, 0, 0);
  WINDOW *game = newwin(10, 10, 1, 1);
  WINDOW *next = newwin(10, 10, 2, 2);
  WINDOW *info = newwin(10, 10, 3, 3);
  WINDOW *control = newwin(10, 10, 4, 4);
  setMenuWin(menu);
  setGameWin(game);
  setNextWin(next);
  setInfoWin(info);
  setControlWin(control);
  endInterface();
  ck_assert(getGameWin() == NULL);
  ck_assert(getMenuWin() == NULL);
  ck_assert(getNextWin() == NULL);
  ck_assert(getInfoWin() == NULL);
  ck_assert(getControlWin() == NULL);
}
END_TEST

START_TEST(no_windows) {
  endInterface();
  ck_assert(isendwin() == TRUE);
}
END_TEST

START_TEST(partial_windows) {
  WINDOW *menu = newwin(10, 10, 0, 0);
  WINDOW *game = newwin(10, 10, 1, 1);
  setMenuWin(menu);
  setGameWin(game);
  endInterface();
  ck_assert(getGameWin() == NULL);
  ck_assert(getMenuWin() == NULL);
}
END_TEST

int endInterfaceTest(void) {
  Suite *s = suite_create("endInterfaceTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, all_windows);
  tcase_add_test(tc_core, no_windows);
  tcase_add_test(tc_core, partial_windows);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
