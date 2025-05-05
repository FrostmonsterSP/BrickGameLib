#include <check.h>
#include <engine.h>

#include "../brick_game/tetris/current_figure.h"
#include "../brick_game/tetris/private.h"

START_TEST(setLeftEdge_noEmptyColumns) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setLeftEdge();
  ck_assert_int_eq(getCurrFigLeftEdge(), 0);
}
END_TEST

START_TEST(setLeftEdge_oneEmptyColumn) {
  setCurrFigType(0);
  setCurrFigRotation(0);
  setLeftEdge();
  ck_assert_int_eq(getCurrFigLeftEdge(), 1);
}
END_TEST

START_TEST(setRightEdge_emptyColumns) {
  setCurrFigType(0);
  setCurrFigRotation(0);
  setRightEdge();
  ck_assert_int_eq(getCurrFigRightEdge(), 2);
}
END_TEST

START_TEST(setRightEdge_noEmptyColumns) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setRightEdge();
  ck_assert_int_eq(getCurrFigRightEdge(), 0);
}
END_TEST

START_TEST(rotateCurrFig_no_overlap) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(0);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  rotateCurrFig();
  ck_assert_int_eq(getCurrFigRotation(), 1);
  ck_assert_int_eq(getCurrFigLeftEdge(), 0);
  ck_assert_int_eq(getCurrFigRightEdge(), 0);
}
END_TEST

START_TEST(rotateCurrFig_overlap) {
  setCurrFigType(0);
  setCurrFigRotation(0);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  setFieldCell(0, 0, 1);
  setFieldCell(1, 0, 1);
  setFieldCell(2, 0, 1);
  setFieldCell(3, 0, 1);
  rotateCurrFig();
  ck_assert_int_eq(getCurrFigRotation(), 0);
  ck_assert_int_eq(getCurrFigLeftEdge(), 1);
  ck_assert_int_eq(getCurrFigRightEdge(), 2);
}
END_TEST

START_TEST(rotateCurrFig_left_edge_of_field) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(0);
  setCurrFigCoordX(-1);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  rotateCurrFig();
  ck_assert_int_eq(getCurrFigRotation(), 1);
  ck_assert_int_eq(getCurrFigLeftEdge(), 0);
  ck_assert_int_eq(getCurrFigRightEdge(), 0);
  ck_assert_int_eq(getCurrFigCoordX(), 0);
}
END_TEST

START_TEST(rotateCurrFig_right_edge_of_field) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(0);
  setCurrFigCoordX(FIELD_WIDTH - FIGURE_WIDTH + 1);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  rotateCurrFig();
  ck_assert_int_eq(getCurrFigRotation(), 1);
  ck_assert_int_eq(getCurrFigLeftEdge(), 0);
  ck_assert_int_eq(getCurrFigRightEdge(), 0);
  ck_assert_int_ne(getCurrFigCoordX(), FIELD_WIDTH - FIGURE_WIDTH + 1);
}
END_TEST

START_TEST(moveCurrFig_left_no_coll) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(5);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  moveCurrFig(DIR_LEFT);
  ck_assert_int_eq(getCurrFigCoordX(), 4);
}
END_TEST

START_TEST(moveCurrFig_left_block_coll) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(5);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  setFieldCell(1, 4, 1);
  moveCurrFig(DIR_LEFT);
  ck_assert_int_eq(getCurrFigCoordX(), 5);
}
END_TEST

START_TEST(moveCurrFig_left_left_edge) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  moveCurrFig(DIR_LEFT);
  ck_assert_int_eq(getCurrFigCoordX(), 0);
}
END_TEST

START_TEST(moveCurrFig_right_no_coll) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  moveCurrFig(DIR_RIGHT);
  ck_assert_int_eq(getCurrFigCoordX(), 1);
}
END_TEST

START_TEST(moveCurrFig_right_block_coll) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  setFieldCell(1, FIGURE_WIDTH, 1);
  moveCurrFig(DIR_RIGHT);
  ck_assert_int_eq(getCurrFigCoordX(), 0);
}
END_TEST

START_TEST(moveCurrFig_right_right_edge) {
  int x = FIELD_WIDTH - FIGURE_WIDTH;
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(x);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  moveCurrFig(DIR_RIGHT);
  ck_assert_int_eq(getCurrFigCoordX(), x);
}
END_TEST

START_TEST(checkNextLine_down_possible) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  int is_possible = checkNextLine();
  ck_assert(is_possible);
}
END_TEST

START_TEST(checkNextLine_down_impossible) {
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  setFieldCell(2, 0, 1);
  int is_possible = checkNextLine();
  ck_assert(!is_possible);
}
END_TEST

START_TEST(checkNextLine_down_at_bottom) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(0);
  setCurrFigCoordY(FIELD_HEIGHT - 1);
  setLeftEdge();
  setRightEdge();
  int is_possible = checkNextLine();
  ck_assert(!is_possible);
}
END_TEST

START_TEST(putCurrFig_in_field) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(2);
  setCurrFigCoordY(2);
  setLeftEdge();
  setRightEdge();
  putCurrFig();
  int field_y = getCurrFigCoordY() + 1;
  for (int j = 0; j < FIGURE_WIDTH; j++) {
    int field_x = getCurrFigCoordX() + j;
    ck_assert_int_eq(getFieldCell(field_y, field_x), 1);
  }
}
END_TEST

START_TEST(putCurrFig_out_of_field_y) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(2);
  setCurrFigCoordY(-2);
  setLeftEdge();
  setRightEdge();
  putCurrFig();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(getFieldCell(i, j), 0);
    }
  }
}
END_TEST

START_TEST(putCurrFig_out_of_field_x) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(0);
  setCurrFigCoordX(-3);
  setCurrFigCoordY(-2);
  setLeftEdge();
  setRightEdge();
  putCurrFig();
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(getFieldCell(i, j), 0);
    }
  }
}
END_TEST

START_TEST(putCurrFig_part_out_of_field_left) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(-2);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  putCurrFig();
  int field_y = getCurrFigCoordY() + 1;
  for (int j = 0; j < FIGURE_WIDTH; j++) {
    if (j < 2) {
      ck_assert_int_eq(getFieldCell(field_y, j), 1);
    } else {
      ck_assert_int_eq(getFieldCell(field_y, j), 0);
    }
  }
}
END_TEST

START_TEST(putCurrFig_part_out_of_field_right) {
  initField();
  setCurrFigType(0);
  setCurrFigRotation(1);
  setCurrFigCoordX(FIELD_WIDTH - 2);
  setCurrFigCoordY(0);
  setLeftEdge();
  setRightEdge();
  putCurrFig();
  int field_y = getCurrFigCoordY() + 1;
  for (int j = FIELD_WIDTH - 1; j >= FIELD_WIDTH - FIGURE_WIDTH; j--) {
    if (j > FIELD_WIDTH - 3) {
      ck_assert_int_eq(getFieldCell(field_y, j), 1);
    } else {
      ck_assert_int_eq(getFieldCell(field_y, j), 0);
    }
  }
}
END_TEST

int currentFigureTest(void) {
  Suite *s = suite_create("currentFigureTest");
  TCase *set_left_edge_tc = tcase_create("setLeftEdge");
  TCase *set_right_edge_tc = tcase_create("setRightEdge");
  TCase *rotate_curr_fig_tc = tcase_create("rotateCurrFig");
  TCase *move_curr_fig_tc = tcase_create("moveCurrFig");
  TCase *check_next_line_tc = tcase_create("checkNextLine");
  TCase *put_curr_fig_tc = tcase_create("putCurrFig");
  tcase_add_test(set_left_edge_tc, setLeftEdge_noEmptyColumns);
  tcase_add_test(set_left_edge_tc, setLeftEdge_oneEmptyColumn);
  tcase_add_test(set_right_edge_tc, setRightEdge_emptyColumns);
  tcase_add_test(set_right_edge_tc, setRightEdge_noEmptyColumns);
  tcase_add_test(rotate_curr_fig_tc, rotateCurrFig_no_overlap);
  tcase_add_test(rotate_curr_fig_tc, rotateCurrFig_overlap);
  tcase_add_test(rotate_curr_fig_tc, rotateCurrFig_left_edge_of_field);
  tcase_add_test(rotate_curr_fig_tc, rotateCurrFig_right_edge_of_field);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_left_no_coll);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_left_block_coll);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_left_left_edge);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_right_no_coll);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_right_block_coll);
  tcase_add_test(move_curr_fig_tc, moveCurrFig_right_right_edge);
  tcase_add_test(check_next_line_tc, checkNextLine_down_possible);
  tcase_add_test(check_next_line_tc, checkNextLine_down_impossible);
  tcase_add_test(check_next_line_tc, checkNextLine_down_at_bottom);
  tcase_add_test(put_curr_fig_tc, putCurrFig_in_field);
  tcase_add_test(put_curr_fig_tc, putCurrFig_out_of_field_y);
  tcase_add_test(put_curr_fig_tc, putCurrFig_out_of_field_x);
  tcase_add_test(put_curr_fig_tc, putCurrFig_part_out_of_field_left);
  tcase_add_test(put_curr_fig_tc, putCurrFig_part_out_of_field_right);
  suite_add_tcase(s, set_left_edge_tc);
  suite_add_tcase(s, set_right_edge_tc);
  suite_add_tcase(s, rotate_curr_fig_tc);
  suite_add_tcase(s, move_curr_fig_tc);
  suite_add_tcase(s, check_next_line_tc);
  suite_add_tcase(s, put_curr_fig_tc);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
