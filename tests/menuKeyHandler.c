#include <check.h>

#include "../gui/cli/cli.h"
#include "engine.h"

START_TEST(menu_key_up_handler) {
  MenuItem_t item = Play;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, Exit);

  item = Speed;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, LevelRestart);

  item = Exit;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, Speed);

  item = IncLevel;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, Play);

  item = DecLevel;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, Play);

  item = IncSpeed;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, LevelRestart);

  item = DecSpeed;
  menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(item, LevelRestart);
}
END_TEST

START_TEST(menu_key_down_handler) {
  MenuItem_t item = Play;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, LevelRestart);

  item = LevelRestart;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Speed);

  item = Exit;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Play);

  item = IncLevel;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Speed);

  item = DecLevel;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Speed);

  item = IncSpeed;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Exit);

  item = DecSpeed;
  menuKeyHandler(0, Down, &item);
  ck_assert_int_eq(item, Exit);
}
END_TEST

START_TEST(menu_key_left_handler) {
  MenuItem_t item = IncLevel;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecLevel);

  item = DecLevel;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecLevel);

  item = IncSpeed;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecSpeed);

  item = DecSpeed;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecSpeed);

  item = LevelRestart;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecLevel);

  item = Speed;
  menuKeyHandler(0, Left, &item);
  ck_assert_int_eq(item, DecSpeed);
}
END_TEST

START_TEST(menu_key_right_handler) {
  MenuItem_t item = DecLevel;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncLevel);

  item = IncLevel;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncLevel);

  item = DecSpeed;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncSpeed);

  item = IncSpeed;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncSpeed);

  item = LevelRestart;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncLevel);

  item = Speed;
  menuKeyHandler(0, Right, &item);
  ck_assert_int_eq(item, IncSpeed);
}
END_TEST

START_TEST(menu_action_handler) {
  MenuItem_t item = Play;
  int action_triggered = menuKeyHandler(0, Action, &item);
  ck_assert_int_eq(action_triggered, 1);

  action_triggered = menuKeyHandler(0, Up, &item);
  ck_assert_int_eq(action_triggered, 0);
}
END_TEST

START_TEST(menu_idle_state) {
  MenuItem_t item = Exit;
  menuKeyHandler(1, Up, &item);
  ck_assert_int_eq(item, LevelRestart);

  item = LevelRestart;
  menuKeyHandler(1, Down, &item);
  ck_assert_int_eq(item, Exit);

  item = Play;
  menuKeyHandler(1, Down, &item);
  ck_assert_int_eq(item, LevelRestart);
  menuKeyHandler(1, Up, &item);
  ck_assert_int_eq(item, Play);
}
END_TEST

START_TEST(menu_default_action) {
  MenuItem_t item = Play;
  menuKeyHandler(1, -1, &item);
  ck_assert_int_eq(item, Play);

  menuKeyHandler(0, -1, &item);
  ck_assert_int_eq(item, Play);
}
END_TEST

int menuKeyHandlerTest(void) {
  Suite *s = suite_create("menuKeyHandlerTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, menu_key_up_handler);
  tcase_add_test(tc_core, menu_key_down_handler);
  tcase_add_test(tc_core, menu_key_left_handler);
  tcase_add_test(tc_core, menu_key_right_handler);
  tcase_add_test(tc_core, menu_action_handler);
  tcase_add_test(tc_core, menu_idle_state);
  tcase_add_test(tc_core, menu_default_action);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
