#include <check.h>
#include <interface.h>

#include "../gui/cli/cli.h"

START_TEST(test_IncLevel) {
  MenuItem_t current_item = IncLevel;
  UserAction_t expected_action = Right;
  UserAction_t actual_action = menuUserInputMod(current_item);
  ck_assert_int_eq(expected_action, actual_action);
}
END_TEST

START_TEST(test_DecLevel) {
  MenuItem_t current_item = DecLevel;
  UserAction_t expected_action = Left;
  UserAction_t actual_action = menuUserInputMod(current_item);
  ck_assert_int_eq(expected_action, actual_action);
}
END_TEST

START_TEST(test_IncSpeed) {
  MenuItem_t current_item = IncSpeed;
  UserAction_t expected_action = Up;
  UserAction_t actual_action = menuUserInputMod(current_item);
  ck_assert_int_eq(expected_action, actual_action);
}
END_TEST

START_TEST(test_DecSpeed) {
  MenuItem_t current_item = DecSpeed;
  UserAction_t expected_action = Down;
  UserAction_t actual_action = menuUserInputMod(current_item);
  ck_assert_int_eq(expected_action, actual_action);
}
END_TEST

START_TEST(test_InvalidItem) {
  MenuItem_t current_item = (MenuItem_t)-1;  // invalid item
  UserAction_t expected_action = -1;
  UserAction_t actual_action = menuUserInputMod(current_item);
  ck_assert_int_eq(expected_action, actual_action);
}
END_TEST

int menuUserInputModTest(void) {
  Suite *s = suite_create("menuUserInputModTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, test_IncLevel);
  tcase_add_test(tc_core, test_DecLevel);
  tcase_add_test(tc_core, test_IncSpeed);
  tcase_add_test(tc_core, test_DecSpeed);
  tcase_add_test(tc_core, test_InvalidItem);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
