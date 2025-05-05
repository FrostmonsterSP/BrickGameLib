#include <check.h>
#include <ncurses.h>
#include <tests.h>

#include "../gui/cli/cli.h"

START_TEST(true_even) {
  initscr();
  setMenuWin(newwin(MENU_HEIGHT, MENU_WIDTH, 0, 0));
  box(getMenuWin(), 0, 0);
  int draw_condition = 1;
  MenuItem_t current_item = 2;
  int line_y = 1;
  drawPlusMinus(draw_condition, current_item, line_y);
  char buffer1[4] = {0};
  char buffer2[4] = {0};
  mvwinnstr(getMenuWin(), line_y, INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1,
            buffer1, 3);
  mvwinnstr(getMenuWin(), line_y, 1, buffer2, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(buffer1, "[+]");
  ck_assert_str_eq(buffer2, "[-]");
}
END_TEST

START_TEST(true_odd) {
  initscr();
  setMenuWin(newwin(MENU_HEIGHT, MENU_WIDTH, 0, 0));
  box(getMenuWin(), 0, 0);
  int draw_condition = 1;
  MenuItem_t current_item = 3;
  int line_y = 1;
  drawPlusMinus(draw_condition, current_item, line_y);
  char buffer1[4] = {0};
  char buffer2[4] = {0};
  mvwinnstr(getMenuWin(), line_y, INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1,
            buffer1, 3);
  mvwinnstr(getMenuWin(), line_y, 1, buffer2, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(buffer1, "[+]");
  ck_assert_str_eq(buffer2, "[-]");
}
END_TEST

START_TEST(test_false) {
  initscr();
  setMenuWin(newwin(MENU_HEIGHT, MENU_WIDTH, 0, 0));
  box(getMenuWin(), 0, 0);
  int draw_condition = 0;
  MenuItem_t current_item = 2;
  int line_y = 1;
  drawPlusMinus(draw_condition, current_item, line_y);
  char buffer1[4] = {0};
  char buffer2[4] = {0};
  mvwinnstr(getMenuWin(), line_y, INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1,
            buffer1, 3);
  mvwinnstr(getMenuWin(), line_y, 1, buffer2, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(buffer1, "   ");
  ck_assert_str_eq(buffer2, "   ");
}
END_TEST

START_TEST(chosen_point_even) {
  initscr();
  setMenuWin(newwin(MENU_HEIGHT, MENU_WIDTH, 0, 0));
  box(getMenuWin(), 0, 0);
  int draw_condition = 1;
  MenuItem_t current_item = Exit + 1;
  int line_y = 1;
  drawPlusMinus(draw_condition, current_item, line_y);
  char buffer1[4] = {0};
  char buffer2[4] = {0};
  mvwinnstr(getMenuWin(), line_y, INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1,
            buffer1, 3);
  mvwinnstr(getMenuWin(), line_y, 1, buffer2, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(buffer1, "[+]");
  ck_assert_str_eq(buffer2, "[-]");
}
END_TEST

START_TEST(chosen_point_odd) {
  initscr();
  setMenuWin(newwin(MENU_HEIGHT, MENU_WIDTH, 0, 0));
  box(getMenuWin(), 0, 0);
  int draw_condition = 1;
  MenuItem_t current_item = Exit + 2;
  int line_y = 1;
  drawPlusMinus(draw_condition, current_item, line_y);
  char buffer1[4] = {0};
  char buffer2[4] = {0};
  mvwinnstr(getMenuWin(), line_y, INIT_MENU_ITEM_X + INIT_MENU_ITEM_L + 1,
            buffer1, 3);
  mvwinnstr(getMenuWin(), line_y, 1, buffer2, 3);
  wclear(getMenuWin());
  delwin(getMenuWin());
  setMenuWin(NULL);
  endwin();
  ck_assert_str_eq(buffer1, "[+]");
  ck_assert_str_eq(buffer2, "[-]");
}
END_TEST

int drawPlusMinusTest(void) {
  Suite *s = suite_create("drawPlusMinusTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, true_even);
  tcase_add_test(tc_core, true_odd);
  tcase_add_test(tc_core, test_false);
  tcase_add_test(tc_core, chosen_point_even);
  tcase_add_test(tc_core, chosen_point_odd);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
