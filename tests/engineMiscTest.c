#include <check.h>
#include <engine.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(incGameLevel_less_than_max) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  incGameLevel();
  ck_assert_int_eq(getGameLevel(), 2);
}
END_TEST

START_TEST(incGameLevel_equal_to_max) {
  setGameLevel(MAX_LEVEL);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  incGameLevel();
  ck_assert_int_eq(getGameLevel(), MAX_LEVEL);
}
END_TEST

START_TEST(incGameSpeed_equal_to_max) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(MAX_SPEED);
  setGameState(1);
  incGameSpeed();
  ck_assert_int_eq(getGameSpeed(), MAX_SPEED);
}
END_TEST

START_TEST(decGameLevel_greater_than_1) {
  setGameLevel(2);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  decGameLevel();
  ck_assert_int_eq(getGameLevel(), 1);
}
END_TEST

START_TEST(decGameLevel_equal_to_1) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  decGameLevel();
  ck_assert_int_eq(getGameLevel(), 1);
}
END_TEST

START_TEST(decGameSpeed_greater_than_1) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(2);
  setGameState(1);
  decGameSpeed();
  ck_assert_int_eq(getGameSpeed(), 1);
}
END_TEST

START_TEST(decGameSpeed_equal_to_1) {
  setGameLevel(1);
  setGameScore(1);
  setGameHighScore(1);
  setGameSpeed(1);
  setGameState(1);
  decGameSpeed();
  ck_assert_int_eq(getGameSpeed(), 1);
}

int engineMiscTest(void) {
  Suite *s = suite_create("engineMiscTest");
  TCase *tc_core = tcase_create("Engine");
  tcase_add_test(tc_core, incGameLevel_less_than_max);
  tcase_add_test(tc_core, incGameLevel_equal_to_max);
  tcase_add_test(tc_core, incGameSpeed_equal_to_max);
  tcase_add_test(tc_core, decGameLevel_greater_than_1);
  tcase_add_test(tc_core, decGameLevel_equal_to_1);
  tcase_add_test(tc_core, decGameSpeed_greater_than_1);
  tcase_add_test(tc_core, decGameSpeed_equal_to_1);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
