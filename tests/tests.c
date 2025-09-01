#include "tests.h"

#include <stdio.h>

int main(void) {
  printf(
      "===============================\n"
      "==== ТЕСТЫ ИГРОВОГО ДВИЖКА ====\n"
      "===============================\n");
  int number_failed = setHighScoreTest();
  number_failed += saveHighScoreTest();
  number_failed += initFieldTest();
  number_failed += clearLineTest();
  number_failed += moveFieldTest();
  number_failed += checkLinesTest();
  number_failed += engineMiscTest();
  number_failed += updateCurrentStateTest();
  number_failed += userInputTest();
  number_failed += handleEventTest();
  number_failed += currentFigureTest();
  return number_failed;
}
