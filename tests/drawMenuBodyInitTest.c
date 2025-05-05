#include <check.h>

#include "../gui/cli/cli.h"

START_TEST(clears_menu_area) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(Play);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      char c = mvinch(i, j);
      ck_assert(c == ' ');
    }
  }
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
}
END_TEST

START_TEST(prints_play_with_reverse_attribute) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(Play);
  char expected[] = "Play  ";
  char actual[7] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y, INIT_MENU_ITEM_X, actual, 6);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected, actual);
  ck_assert(!(getattrs(getMenuWin()) & A_REVERSE));
}
END_TEST

START_TEST(prints_level_and_speed_without_reverse_attribute) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(LevelRestart);
  char expected[] = "Level ";
  char actual[7] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, INIT_MENU_ITEM_X, actual, 6);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected, actual);
  ck_assert(!(getattrs(getMenuWin()) & A_REVERSE));
}
END_TEST

START_TEST(calls_drawPlusMinus_Level) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(LevelRestart);
  char expected_minus[] = "[-]";
  char expected_plus[] = "[+]";
  char actual_minus[4] = {0};
  char actual_plus[4] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, 1, actual_minus, 3);
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1,
            INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1, actual_plus, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected_minus, actual_minus);
  ck_assert_str_eq(expected_plus, actual_plus);
}
END_TEST

START_TEST(calls_drawPlusMinus_Speed) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(Speed);
  char expected_minus[] = "[-]";
  char expected_plus[] = "[+]";
  char actual_minus[4] = {0};
  char actual_plus[4] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 2, 1, actual_minus, 3);
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 2,
            INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1, actual_plus, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected_minus, actual_minus);
  ck_assert_str_eq(expected_plus, actual_plus);
}
END_TEST

START_TEST(calls_drawPlusMinus_inc) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(IncSpeed);
  char expected_minus[] = "[-]";
  char expected_plus[] = "[+]";
  char actual_minus[4] = {0};
  char actual_plus[4] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 2, 1, actual_minus, 3);
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 2,
            INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1, actual_plus, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected_minus, actual_minus);
  ck_assert_str_eq(expected_plus, actual_plus);
}
END_TEST

START_TEST(calls_drawPlusMinus_dec) {
  setMenuWin(newwin(GW_HEIGHT, GW_WIDTH, GW_POS_Y, GW_POS_X));
  drawMenuBodyInit(DecLevel);
  char expected_minus[] = "[-]";
  char expected_plus[] = "[+]";
  char actual_minus[4] = {0};
  char actual_plus[4] = {0};
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1, 1, actual_minus, 3);
  mvwinnstr(getMenuWin(), INIT_MENU_ITEM_Y + 1,
            INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1, actual_plus, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(expected_minus, actual_minus);
  ck_assert_str_eq(expected_plus, actual_plus);
}
END_TEST

int drawMenuBodyInitTest(void) {
  Suite *s = suite_create("drawMenuBodyInitTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, clears_menu_area);
  tcase_add_test(tc_core, prints_play_with_reverse_attribute);
  tcase_add_test(tc_core, prints_level_and_speed_without_reverse_attribute);
  tcase_add_test(tc_core, calls_drawPlusMinus_Level);
  tcase_add_test(tc_core, calls_drawPlusMinus_Speed);
  tcase_add_test(tc_core, calls_drawPlusMinus_inc);
  tcase_add_test(tc_core, calls_drawPlusMinus_dec);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
