#include <check.h>
#include <interface.h>
#include <stdlib.h>

#include "../gui/cli/cli.h"

START_TEST(empty) {
  GameInfo_t game_info;
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      game_info.field[y][x] = 0;
    }
  }
  startInterface();
  drawGameField(&game_info);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      ck_assert_int_eq(mvwinch(getGameWin(), y, x1), ' ');
      ck_assert_int_eq(mvwinch(getGameWin(), y, x2), ' ');
    }
  }
  endInterface();
}
END_TEST

START_TEST(full) {
  GameInfo_t game_info;
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      game_info.field[y][x] = 1;
    }
  }
  startInterface();
  drawGameField(&game_info);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      ck_assert_int_eq(mvwinch(getGameWin(), y, x1), '[');
      ck_assert_int_eq(mvwinch(getGameWin(), y, x2), ']');
    }
  }
  endInterface();
}
END_TEST

START_TEST(random) {
  GameInfo_t game_info;
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      game_info.field[y][x] = (rand() % 2);
    }
  }
  startInterface();
  drawGameField(&game_info);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      if (game_info.field[i][j]) {
        ck_assert_int_eq(mvwinch(getGameWin(), y, x1), '[');
        ck_assert_int_eq(mvwinch(getGameWin(), y, x2), ']');
      } else {
        ck_assert_int_eq(mvwinch(getGameWin(), y, x1), ' ');
        ck_assert_int_eq(mvwinch(getGameWin(), y, x2), ' ');
      }
    }
  }
  endInterface();
}
END_TEST

int drawGameFieldTest(void) {
  Suite *s = suite_create("drawGameFieldTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, empty);
  tcase_add_test(tc_core, full);
  tcase_add_test(tc_core, random);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
