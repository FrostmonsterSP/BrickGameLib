#include <check.h>
#include <engine.h>

#include "../brick_game/tetris/private.h"

START_TEST(TestStart) {
  setGameState(StateInit);
  UserAction_t action = Start;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateSpawn);
}
END_TEST

START_TEST(TestPause) {
  setGameState(StateAction);
  UserAction_t action = Pause;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateIdle);
}
END_TEST

START_TEST(TestTerminate) {
  setGameState(StateAction);
  UserAction_t action = Terminate;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateInit);
}
END_TEST

START_TEST(TestLeft) {
  setGameState(StateAction);
  UserAction_t action = Left;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(TestRight) {
  setGameState(StateAction);
  UserAction_t action = Right;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(TestUp) {
  setGameState(StateAction);
  UserAction_t action = Up;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(TestDown) {
  setGameState(StateAction);
  UserAction_t action = Down;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateShift);
}
END_TEST

START_TEST(TestAction) {
  setGameState(StateAction);
  UserAction_t action = Action;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(TestUnknown) {
  setGameState(StateInit);
  UserAction_t action = (UserAction_t)100;
  userInput(action);
  ck_assert_int_eq(getGameState(), StateInit);
}
END_TEST

int userInputTest(void) {
  Suite *s = suite_create("UserInput");
  TCase *tc_core = tcase_create("Updaters");
  tcase_add_test(tc_core, TestStart);
  tcase_add_test(tc_core, TestPause);
  tcase_add_test(tc_core, TestTerminate);
  tcase_add_test(tc_core, TestLeft);
  tcase_add_test(tc_core, TestRight);
  tcase_add_test(tc_core, TestUp);
  tcase_add_test(tc_core, TestDown);
  tcase_add_test(tc_core, TestAction);
  tcase_add_test(tc_core, TestUnknown);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
