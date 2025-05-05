#include <check.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"
#include "engine.h"

START_TEST(level0) {
  setGameLevel(1);
  initField();
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      ck_assert_int_eq(getFieldCell(y, x), 0);
    }
  }
}
END_TEST

START_TEST(level) {
  setGameLevel(_i);
  initField();
  int game_level = getGameLevel();
  ck_assert_int_eq(game_level, _i);
  int start_y = FIELD_HEIGHT - 1;
  int end_y = FIELD_HEIGHT - game_level;
  for (int y = start_y; y > end_y; y--) {
    int level_filled_line = 0;
    for (int x = 0; x < FIELD_WIDTH && !level_filled_line; x++) {
      level_filled_line = getFieldCell(y, x);
    }
    ck_assert_int_eq(level_filled_line, 1);
  }
}
END_TEST

int initFieldTest(void) {
  Suite *s = suite_create("Engine 3");
  TCase *tc_core = tcase_create("initFieldTest");
  tcase_add_test(tc_core, level0);
  tcase_add_loop_test(tc_core, level, 2, MAX_LEVEL);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
