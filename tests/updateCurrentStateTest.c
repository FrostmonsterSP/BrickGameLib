#include <check.h>
#include <engine.h>

#include "../brick_game/tetris/current_figure.h"
#include "../brick_game/tetris/private.h"

static inline void fillLine(int val) {
  int row_indx = -1;
  for (int i = 0; row_indx < 0 && i < FIGURE_WIDTH; i++) {
    row_indx = getCurrFigRowsToCheck(i);
  }
  row_indx += getCurrFigCoordY() + 1;
  for (int fx = 0; fx < FIELD_WIDTH; fx++) {
    setFieldCell(row_indx, fx, val);
  }
}

START_TEST(State_0) {
  setGameState(State0);
  const GameInfo_t *game_info = updateCurrentState();
  ck_assert_ptr_nonnull(game_info);
  ck_assert_int_eq(game_info->state, StateInit);
}
END_TEST

START_TEST(StateShift_CheckNextLineFalse) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateShift);
  initField();
  ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(StateShift_CheckNextLineTrue) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateShift);
  initField();
  fillLine(1);
  ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateSpawn);
}
END_TEST

START_TEST(StateSpawn_CheckNextLineFalse) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateSpawn);
  initField();
  ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(StateSpawn_CheckNextLineTrue) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateSpawn);
  initField();
  fillLine(1);
  ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateInit);
}
END_TEST

START_TEST(Default) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateAction);
  initField();
  ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateAction);
}
END_TEST

START_TEST(Timer0) {
  newNextFigure();
  setNewCurrFig();
  setGameState(StateAction);
  initField();
  int time = DEFAULT_SPEED + 1;
  while (time--) ck_assert_ptr_nonnull(updateCurrentState());
  ck_assert_int_eq(getGameState(), StateShift);
}
END_TEST

int updateCurrentStateTest(void) {
  Suite *s = suite_create("updateCurrentStateTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, State_0);
  tcase_add_test(tc_core, StateShift_CheckNextLineFalse);
  tcase_add_test(tc_core, StateShift_CheckNextLineTrue);
  tcase_add_test(tc_core, StateSpawn_CheckNextLineFalse);
  tcase_add_test(tc_core, StateSpawn_CheckNextLineTrue);
  tcase_add_test(tc_core, Default);
  tcase_add_test(tc_core, Timer0);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
