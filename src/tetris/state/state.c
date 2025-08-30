#include "state.h"
#include "tetris/event_handlers/event_handlers.h"
#include "tetris/figures/current_figure.h"

#include <engine.h>

/* Определяет различные состояния, в которых может находиться игра. */
static GameState_t state;

static int Timer = DEFAULT_SPEED;

void setGameState(int newState) { state = newState; }

int getGameState(void) { return state; }

const GameInfo_t *updateCurrentState(void) {
  switch (getGameState()) {
  case State0:
    handleEvent(EventInit);
    break;
  case StateShift:
  case StateSpawn:
    if (!checkNextLine()) {
      handleEvent(EventTouchdown);
    } else {
      handleEvent(EventPlaceFree);
    }
    break;
  default:
    break;
  }
  if (Timer > 0) {
    Timer--;
  } else {
    handleEvent(EventTick);
  }
  return &GameInfo;
}
