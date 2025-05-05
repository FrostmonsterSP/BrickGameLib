#include <check.h>
#include <interface.h>
#include <stdlib.h>

#include "../gui/cli/cli.h"

START_TEST(drawNextPiece_not_null) {
  GameInfo_t game_info;
  int **next = (int *[]){(int[]){1, 1, 1, 1}, (int[]){0, 0, 0, 0},
                         (int[]){1, 1, 1, 1}, (int[]){0, 0, 0, 0}};
  game_info.next = next;
  startInterface();
  drawNextPiece(&game_info);
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      if (game_info.next[i][j]) {
        ck_assert_int_eq(mvwinch(getNextWin(), y, x1), '[');
        ck_assert_int_eq(mvwinch(getNextWin(), y, x2), ']');
      } else {
        ck_assert_int_eq(mvwinch(getNextWin(), y, x1), ' ');
        ck_assert_int_eq(mvwinch(getNextWin(), y, x2), ' ');
      }
    }
  }
  endInterface();
}

END_TEST

START_TEST(drawNextPiece_null) {
  GameInfo_t game_info;
  game_info.next = NULL;
  startInterface();
  drawNextPiece(&game_info);
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      ck_assert_int_eq(mvwinch(getNextWin(), y, x1), ' ');
      ck_assert_int_eq(mvwinch(getNextWin(), y, x2), ' ');
    }
  }
  endInterface();
}
END_TEST

START_TEST(drawNextPiece_empty) {
  GameInfo_t game_info;
  int **next = (int *[]){(int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0},
                         (int[]){0, 0, 0, 0}, (int[]){0, 0, 0, 0}};
  game_info.next = next;
  startInterface();
  drawNextPiece(&game_info);
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int y = i + 1;
      int x1 = j * 2 + 1;
      int x2 = x1 + 1;
      ck_assert_int_eq(mvwinch(getNextWin(), y, x1), ' ');
      ck_assert_int_eq(mvwinch(getNextWin(), y, x2), ' ');
    }
  }
  endInterface();
}
END_TEST

int drawNextPieceTest(void) {
  Suite *s = suite_create("drawNextPieceTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, drawNextPiece_not_null);
  tcase_add_test(tc_core, drawNextPiece_null);
  tcase_add_test(tc_core, drawNextPiece_empty);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
