#include <check.h>
#include <interface.h>

#include "../gui/cli/cli.h"

START_TEST(output) {
  startInterface();
  drawControlPanel();
  char expected_controls[] = "Controls:";
  char expected_keys[] = "  Arrow keys:  Move ";
  char expected_space[] = "  Space:       Drop ";
  char expected_start[] = "  S:           Start game";
  char expected_pause[] = "  P:           Pause";
  char expected_quit[] = "  Q:           Quit ";
  char actual_controls[10] = {0};
  char actual_keys[21] = {0};
  char actual_start[26] = {0};
  char actual_pause[21] = {0};
  char actual_space[21] = {0};
  char actual_quit[21] = {0};
  mvwinnstr(getControlWin(), 0, 1, actual_controls, 9);
  mvwinnstr(getControlWin(), 1, 1, actual_keys, 20);
  mvwinnstr(getControlWin(), 2, 1, actual_space, 20);
  mvwinnstr(getControlWin(), 3, 1, actual_start, 25);
  mvwinnstr(getControlWin(), 4, 1, actual_pause, 20);
  mvwinnstr(getControlWin(), 5, 1, actual_quit, 20);
  endInterface();
  ck_assert_str_eq(expected_controls, actual_controls);
  ck_assert_str_eq(expected_keys, actual_keys);
  ck_assert_str_eq(expected_space, actual_space);
  ck_assert_str_eq(expected_start, actual_start);
  ck_assert_str_eq(expected_pause, actual_pause);
  ck_assert_str_eq(expected_quit, actual_quit);
}
END_TEST

int drawControlPanelTest(void) {
  Suite *s = suite_create("drawControlPanelTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, output);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
