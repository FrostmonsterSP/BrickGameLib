#include <check.h>
#include <stdio.h>
#include <tests.h>

#include "../brick_game/tetris/private.h"

START_TEST(file_not_exists) {
  remove(getScoreFilePath());
  setGameScore(100);
  setGameHighScore(0);
  saveHighScore();
  FILE *fp = fopen(getScoreFilePath(), "r");
  ck_assert_ptr_nonnull(fp);
  int high_score = 0;
  fread(&high_score, sizeof(int), 1, fp);
  ck_assert_int_eq(high_score, 100);
  fclose(fp);
  remove(getScoreFilePath());
}
END_TEST

START_TEST(file_exists_not_updated) {
  FILE *fp = fopen(getScoreFilePath(), "w");
  ck_assert_ptr_nonnull(fp);
  int high_score = 100;
  fwrite(&high_score, sizeof(int), 1, fp);
  fclose(fp);
  setGameScore(50);
  setGameHighScore(100);
  saveHighScore();
  fp = fopen(getScoreFilePath(), "r");
  ck_assert_ptr_nonnull(fp);
  fread(&high_score, sizeof(int), 1, fp);
  ck_assert_int_eq(high_score, 100);
  fclose(fp);
  remove(getScoreFilePath());
}
END_TEST

START_TEST(file_exists_updated) {
  FILE *fp = fopen(getScoreFilePath(), "w");
  ck_assert_ptr_nonnull(fp);
  int high_score = 100;
  fwrite(&high_score, sizeof(int), 1, fp);
  fclose(fp);
  setGameScore(150);
  setGameHighScore(100);
  saveHighScore();
  fp = fopen(getScoreFilePath(), "r");
  ck_assert_ptr_nonnull(fp);
  fread(&high_score, sizeof(int), 1, fp);
  ck_assert_int_eq(high_score, 150);
  fclose(fp);
  remove(getScoreFilePath());
}
END_TEST

int saveHighScoreTest(void) {
  Suite *s = suite_create("saveHighScoreTest");
  TCase *tc_core = tcase_create("");
  tcase_add_test(tc_core, file_not_exists);
  tcase_add_test(tc_core, file_exists_not_updated);
  tcase_add_test(tc_core, file_exists_updated);
  suite_add_tcase(s, tc_core);
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}
