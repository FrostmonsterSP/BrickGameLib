/**
 * @file engine.c
 * @brief Реализация функций из @ref engine.h
 *
 * @details Данный файл содержит реализации библиотечных функций, объявленных в
 * @ref engine.h, которые необходимы для
 * корректной работы игры.
 */
#include <engine.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "state/state.h"
#include "figures/current_figure.h"
#include "private.h"
#include "figures/figures.h"
#include "figures/next_figure.h"
#include "tetris/event_handlers/event_handlers.h"

/**
 * @brief Структура, содержащая текущую информацию об игре.
 *
 * Включает такие данные, как:
 * - Состояние игры (GameInfo.state)
 * - Текущий уровень (GameInfo.level)
 * - Скорость игры (GameInfo.speed)
 * - Текущий счет (GameInfo.score)
 * - Рекорд (GameInfo.high_score)
 * - Поле игры (GameInfo.field)
 * - Следующая фигура (GameInfo.next)
 */
static GameInfo_t GameInfo = {0};

/**
 * @brief Таймер для отсчета времени между движениями фигур.
 * Используется для управления скоростью падения фигур.
 * По умолчанию инициализируется значением DEFAULT_SPEED.
 */
static int Timer = DEFAULT_SPEED;

void userInput(UserAction_t action) {
  switch (action) {
  case Start:
    handleEvent(EventStart);
    break;
  case Pause:
    handleEvent(EventPause);
    break;
  case Terminate:
    handleEvent(EventTerminate);
    break;
  case Left:
    handleEvent(EventLeft);
    break;
  case Right:
    handleEvent(EventRight);
    break;
  case Up:
    handleEvent(EventUp);
    break;
  case Down:
    handleEvent(EventDown);
    break;
  case Action:
    handleEvent(EventAction);
    break;
  default:
    break;
  }
}

char *getScoreFilePath(void) {
  static char file_path[MAX_FILEPATH] = {0};
  if (file_path[0] == 0) {
    strcat(strcpy(file_path, getenv("HOME")), "/score.bin");
  }
  return file_path;
}

void setHighScore(void) {
  int high_score = 0;
  FILE *fp = fopen(getScoreFilePath(), "r");
  if (fp != NULL) {
    if (fread(&high_score, sizeof(int), 1, fp) != 1) {
      printf("Error fread");
    }
    fclose(fp);
    high_score = high_score < 0 ? 0 : high_score;
  }
  GameInfo.high_score = high_score;
}

void saveHighScore(void) {
  GameInfo.level = 1;
  GameInfo.speed = 1;
  if (GameInfo.score > GameInfo.high_score) {
    FILE *fp = fopen(getScoreFilePath(), "w+");
    GameInfo.high_score = GameInfo.score;
    if (fp != NULL) {
      fwrite(&GameInfo.high_score, sizeof(int), 1, fp);
      fclose(fp);
    }
  }
}

void initField(void) {
  srand(time(NULL));
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      GameInfo.field[y][x] = FIELD_HEIGHT - y < GameInfo.level ? rand() % 2 : 0;
      GameInfo.field[y][x] =
          GameInfo.field[y][x] == 0 ? 0 : rand() % FIGURE_CNT;
    }
  }
}

void clearLine(int y) {
  for (int x = 0; x < FIELD_WIDTH; x++) {
    GameInfo.field[y][x] = 0;
  }
}

void moveField(int y, int min_y) {
  for (int i = y; i > min_y; i--) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      GameInfo.field[i][j] = GameInfo.field[i - 1][j];
    }
  }
  for (int i = 0; i < FIELD_WIDTH; i++) {
    GameInfo.field[min_y][i] = 0;
  }
}

void checkLines(void) {
  int empty_lines = 0;
  int min_line_y = 0;
  for (int y = FIELD_HEIGHT - 1; y >= min_line_y; y--) {
    int cells = 0;
    for (int x = 0; x < FIELD_WIDTH && !cells; x++) {
      cells += !(GameInfo.field[y][x]);
    }
    if (!cells) {
      clearLine(y);
      moveField(y++, min_line_y++);
      empty_lines++;
    }
  }
  if (empty_lines) {
    int new_score = LINE_SCORE(empty_lines);
    if (GameInfo.score / NEXT_LEVEL <
        (GameInfo.score + new_score) / NEXT_LEVEL) {
      GameInfo.level++;
      incGameSpeed();
    }
    GameInfo.score += new_score;
  }
}

void setGameLevel(int score) { GameInfo.level = score; }
void setGameSpeed(int speed) { GameInfo.speed = speed; }
void setGameScore(int score) { GameInfo.score = score; }
void setGameHighScore(int score) { GameInfo.high_score = score; }

void resetTimer(void) {
  Timer = DEFAULT_SPEED - ((DEFAULT_SPEED / MAX_SPEED) * (GameInfo.speed - 1));
}

void incGameLevel(void) {
  if (GameInfo.level < MAX_LEVEL)
    GameInfo.level++;
}

void incGameSpeed(void) {
  if (GameInfo.speed < MAX_SPEED)
    GameInfo.speed++;
}

void decGameLevel(void) {
  if (GameInfo.level > 1)
    GameInfo.level--;
}

void decGameSpeed(void) {
  if (GameInfo.speed > 1)
    GameInfo.speed--;
}

int getGameLevel(void) { return GameInfo.level; }
int getGameSpeed(void) { return GameInfo.speed; }
int getGameScore(void) { return GameInfo.score; }
int getGameHighScore(void) { return GameInfo.high_score; }

int getFieldCell(int y, int x) { return GameInfo.field[y][x]; }

void setGameInfoNext(void) {
  GameInfo.next = getFigureType(getNextFigType(),getNextFigRotation());
}

void setFieldCell(int y, int x, int val) { GameInfo.field[y][x] = val; }
