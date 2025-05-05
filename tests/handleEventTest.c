#include <check.h>
#include <engine.h>

#include "../brick_game/tetris/private.h"

START_TEST(no_matching_state) {
  setGameState(StateInit);
  handleEvent(EventTerminate);
  ck_assert_int_eq(getGameState(), StateInit);
}
END_TEST

START_TEST(matching_state_and_event) {
  setGameState(StateAction);
  handleEvent(EventLeft);
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

int handleEventTest(void) {
  Suite *s = suite_create("handleEventTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, no_matching_state);
  tcase_add_test(tc_core, matching_state_and_event);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
