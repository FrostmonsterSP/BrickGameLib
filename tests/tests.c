#include <stdio.h>
#include <tests.h>

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
  printf(
      "\n"
      "===============================\n"
      "====== ТЕСТЫ  ИНТЕРФЕЙСА ======\n"
      "===============================\n");
  number_failed += drawGameFieldTest();
  number_failed += drawInfoPanelTest();
  number_failed += drawControlPanelTest();
  number_failed += drawNextPieceTest();
  number_failed += endInterfaceTest();
  number_failed += initMenuWinTest();
  number_failed += closeMenuWinTest();
  number_failed += drawPlusMinusTest();
  number_failed += drawMenuBodyInitTest();
  number_failed += drawMenuBodyIdleTest();
  number_failed += drawMenuFooterTest();
  number_failed += menuKeyHandlerTest();
  number_failed += menuUserInputModTest();
  number_failed += drawMenusTest();
  number_failed += interfaceTest();
  return number_failed;
}
