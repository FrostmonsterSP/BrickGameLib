#include <check.h>
#include <stdio.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(exists) {
  FILE *fp = fopen(getScoreFilePath(), "w");
  ck_assert_ptr_nonnull(fp);
  int high_score = 100;
  fwrite(&high_score, sizeof(int), 1, fp);
  fclose(fp);
  setHighScore();
  remove(getScoreFilePath());
  ck_assert_int_eq(getGameHighScore(), 100);
}
END_TEST

START_TEST(exists_invalid_value) {
  FILE *fp = fopen(getScoreFilePath(), "w");
  ck_assert_ptr_nonnull(fp);
  int invalid_value[] = {-2, -4, -1};
  fwrite(invalid_value, sizeof(invalid_value), 1, fp);
  fclose(fp);
  setHighScore();
  remove(getScoreFilePath());
  ck_assert_int_eq(getGameHighScore(), 0);
}
END_TEST

START_TEST(not_exists) {
  setHighScore();
  ck_assert_int_eq(getGameHighScore(), 0);
}
END_TEST

int setHighScoreTest(void) {
  Suite *s = suite_create("setHighScoreTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, exists);
  tcase_add_test(tc_core, exists_invalid_value);
  tcase_add_test(tc_core, not_exists);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
