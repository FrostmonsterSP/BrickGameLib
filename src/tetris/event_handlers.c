#include "event_handlers.h"

#include "current_figure.h"
#include "private.h"

/**
 * @brief Таблица состояний конечного автомата.
 *
 * Таблица описывает переходы между состояниями игры на основе событий.
 */
static StateTransition_t StateTable[] = {
    {State0, EventInit, StateInit, handleEventInit},
    {StateInit, EventRight, StateInit, incGameLevel},
    {StateInit, EventUp, StateInit, incGameSpeed},
    {StateInit, EventLeft, StateInit, decGameLevel},
    {StateInit, EventDown, StateInit, decGameSpeed},
    {StateInit, EventStart, StateSpawn, handleEventStart},
    {StateAction, EventLeft, StateAction, handleEventMoveLeft},
    {StateAction, EventRight, StateAction, handleEventMoveRight},
    {StateAction, EventAction, StateAction, handleEventRotate},
    {StateAction, EventDown, StateShift, handleEventDrop},
    {StateAction, EventTick, StateShift, NULL},
    {StateAction, EventPause, StateIdle, NULL},
    {StateIdle, EventPause, StateAction, NULL},
    {StateIdle, EventStart, StateInit, NULL},
    {StateAction, EventTerminate, StateInit, saveHighScore},
    {StateShift, EventPlaceFree, StateAction, handleEventPlaceFree},
    {StateShift, EventTouchdown, StateSpawn, handleEventTouchdown},
    {StateSpawn, EventPlaceFree, StateAction, handleEventPlaceFree},
    {StateSpawn, EventTouchdown, StateInit, saveHighScore},
};

void handleEvent(int event) {
  unsigned i = 0;
  unsigned max_index = getTransitionTableSize();
  GameState_t current_state = getGameState();
  while (i < max_index && (current_state != StateTable[i].currentState ||
                           (GameEvent_t)event != StateTable[i].event)) {
    i++;
  }
  if (i < max_index) {
    if (StateTable[i].action != NULL) {
      StateTable[i].action();
    }
    setGameState(StateTable[i].nextState);
  }
}

void handleEventInit(void) {
  setHighScore();
  setGameLevel(1);
  setGameSpeed(1);
}

void handleEventStart(void) {
  newNextFigure();
  setNewCurrFig();
  initField();
  setGameLevel(1);
  resetTimer();
}

void handleEventMoveLeft(void) {
  clearCurrFig();
  moveCurrFig(DIR_LEFT);
  putCurrFig();
}

void handleEventMoveRight(void) {
  clearCurrFig();
  moveCurrFig(DIR_RIGHT);
  putCurrFig();
}

void handleEventRotate(void) {
  clearCurrFig();
  rotateCurrFig();
  putCurrFig();
}

void handleEventDrop(void) {
  clearCurrFig();
  while (checkNextLine()) {
    moveCurrFigDown();
  }
  putCurrFig();
}

void handleEventPlaceFree(void) {
  clearCurrFig();
  moveCurrFigDown();
  putCurrFig();
  resetTimer();
}

void handleEventTouchdown(void) {
  checkLines();
  setNewCurrFig();
  putCurrFig();
  resetTimer();
}

int getTransitionTableSize(void) {
  return sizeof(StateTable) / sizeof(StateTransition_t);
}
