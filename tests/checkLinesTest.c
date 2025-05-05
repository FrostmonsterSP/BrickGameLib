#include <check.h>
#include <engine.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(empty_field) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  initField();
  int score = getGameScore();
  int level = getGameLevel();
  checkLines();
  ck_assert_int_eq(getGameScore(), score);
  ck_assert_int_eq(getGameLevel(), level);
}
END_TEST

START_TEST(one_line) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, x, 1);
  }
  int score = getGameScore();
  int level = getGameLevel();
  checkLines();
  ck_assert_int_eq(getGameScore(), score + LINE_SCORE(1));
  ck_assert_int_eq(getGameLevel(), level);
}
END_TEST

START_TEST(two_lines) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, x, 1);
    setFieldCell(1, x, 1);
  }
  int score = getGameScore();
  int level = getGameLevel();
  checkLines();
  ck_assert_int_eq(getGameScore(), score + LINE_SCORE(2));
  ck_assert_int_eq(getGameLevel(), level);
}
END_TEST

START_TEST(tree_lines) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, x, 1);
    setFieldCell(1, x, 1);
    setFieldCell(2, x, 1);
  }
  int score = getGameScore();
  int level = getGameLevel();
  checkLines();
  ck_assert_int_eq(getGameScore(), score + LINE_SCORE(3));
  ck_assert_int_eq(getGameLevel(), level + 1);
}
END_TEST

START_TEST(four_lines) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  initField();
  for (int x = 0; x < FIELD_WIDTH; x++) {
    setFieldCell(0, x, 1);
    setFieldCell(1, x, 1);
    setFieldCell(2, x, 1);
    setFieldCell(4, x, 1);
  }
  int score = getGameScore();
  int level = getGameLevel();
  checkLines();
  ck_assert_int_eq(getGameScore(), score + LINE_SCORE(4));
  ck_assert_int_eq(getGameLevel(), level + 1);
}
END_TEST

int checkLinesTest(void) {
  Suite *s = suite_create("checkLinesTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, empty_field);
  tcase_add_test(tc_core, one_line);
  tcase_add_test(tc_core, two_lines);
  tcase_add_test(tc_core, tree_lines);
  tcase_add_test(tc_core, four_lines);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
