#include <check.h>
#include <engine.h>
#include <interface.h>

#include "../brick_game/tetris/private.h"

START_TEST(initial_state) {
  startInterface();
  updateCurrentState();
  int result = interface();
  endInterface();
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(idle_state) {
  startInterface();
  updateCurrentState();
  setGameState(StateIdle);
  int result = interface();
  endInterface();
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(game_running) {
  startInterface();
  updateCurrentState();
  setGameState(StateAction);
  int result = interface();
  endInterface();
  ck_assert_int_eq(result, 1);
}
END_TEST

int interfaceTest(void) {
  Suite *s = suite_create("interfaceTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, initial_state);
  tcase_add_test(tc_core, idle_state);
  tcase_add_test(tc_core, game_running);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
