#include <check.h>
#include <interface.h>

#include "../gui/cli/cli.h"

START_TEST(nextPiece) {
  GameInfo_t state;
  state.score = 0;
  state.level = 0;
  state.speed = 0;
  state.high_score = 0;
  startInterface();
  drawInfoPanel(&state);
  char expected[] = "Next Piece:";
  char actual[12] = {0};
  mvwinnstr(getInfoWin(), 1, 1, actual, 11);
  ck_assert_str_eq(expected, actual);
  endInterface();
}
END_TEST

START_TEST(score) {
  GameInfo_t state;
  state.score = 100;
  state.level = 0;
  state.speed = 0;
  state.high_score = 0;
  startInterface();
  drawInfoPanel(&state);
  char expected[] = "Score: 100";
  char actual[11] = {0};
  mvwinnstr(getInfoWin(), 2 + NP_HEIGHT, 1, actual, 10);
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(level) {
  GameInfo_t state;
  state.score = 0;
  state.level = 5;
  state.speed = 0;
  state.high_score = 0;
  startInterface();
  drawInfoPanel(&state);
  char expected[] = "Level: 5";
  char actual[9] = {0};
  mvwinnstr(getInfoWin(), 3 + NP_HEIGHT, 1, actual, 8);
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(speed) {
  GameInfo_t state;
  state.score = 0;
  state.level = 0;
  state.speed = 10;
  state.high_score = 0;
  startInterface();
  drawInfoPanel(&state);
  char expected[] = "Speed: 10";
  char actual[10] = {0};
  mvwinnstr(getInfoWin(), 4 + NP_HEIGHT, 1, actual, 9);
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

START_TEST(highScore) {
  GameInfo_t state;
  state.score = 0;
  state.level = 0;
  state.speed = 0;
  state.high_score = 500;
  startInterface();
  drawInfoPanel(&state);
  char expected[] = "High Score: 500";
  char actual[16] = {0};
  mvwinnstr(getInfoWin(), 6 + NP_HEIGHT, 1, actual, 15);
  endInterface();
  ck_assert_str_eq(expected, actual);
}
END_TEST

int drawInfoPanelTest(void) {
  Suite *s = suite_create("drawInfoPanelTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, nextPiece);
  tcase_add_test(tc_core, score);
  tcase_add_test(tc_core, level);
  tcase_add_test(tc_core, speed);
  tcase_add_test(tc_core, highScore);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
