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

#include "current_figure.h"
#include "private.h"

/**
 * @brief Массив, содержащий информацию о фигурах игры в различных состояниях
 * поворота.
 *
 * Каждая фигура представлена как двумерный массив 4x4, где 1 — это клетка
 * фигуры, а 0 — пустая клетка. Фигуры поворачиваются на 90 градусов по часовой
 * стрелке.</br>
 * Размеры:
 * - FIGURE_CNT: количество типов фигур (7 фигур).
 * - FIGURE_ROUNDS: количество возможных поворотов для каждой фигуры (4
 * поворота).
 */
static int **Figures[FIGURE_CNT][FIGURE_ROUNDS] = {
    // clang-format off
    /* Линия (I-образная фигура) */
    {/* Поворот 0 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 0, 0, 0},
         (int[]){1, 1, 1, 1},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){0, 0, 0, 0},
         (int[]){1, 1, 1, 1},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* Обратная L-образная фигура (J-образная) */
    {/* Поворот 0 */
     (int *[]){
         (int[]){1, 0, 0, 0},
         (int[]){1, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 0, 0, 0},
         (int[]){1, 1, 1, 0},
         (int[]){0, 0, 1, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* L-образная фигура */
    {/* Поворот 0 */
     (int *[]){
         (int[]){0, 0, 1, 0},
         (int[]){1, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 0, 0, 0},
         (int[]){1, 1, 1, 0},
         (int[]){1, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* Квадрат (O-образная фигура) */
    {/* Поворот 0 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* T-образная фигура */
    {/* Поворот 0 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){1, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 0, 0, 0},
         (int[]){1, 1, 1, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* Z-образная фигура */
    {/* Поворот 0 */
     (int *[]){
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){1, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 1, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){0, 1, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){1, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     }},
    /* Обратная Z-образная фигура (S-образная) */
    {/* Поворот 0 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 90 */
     (int *[]){
         (int[]){1, 0, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 180 */
     (int *[]){
         (int[]){0, 1, 1, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 0, 0, 0},
         (int[]){0, 0, 0, 0}
     },
     /* Поворот 270 */
     (int *[]){
         (int[]){1, 0, 0, 0},
         (int[]){1, 1, 0, 0},
         (int[]){0, 1, 0, 0},
         (int[]){0, 0, 0, 0}
     }}
    // clang-format on
};

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

const GameInfo_t *updateCurrentState(void) {
  switch (GameInfo.state) {
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
    fread(&high_score, sizeof(int), 1, fp);
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
void setGameState(int state) { GameInfo.state = state; }
void setGameScore(int score) { GameInfo.score = score; }
void setGameHighScore(int score) { GameInfo.high_score = score; }

void resetTimer(void) {
  Timer = DEFAULT_SPEED - ((DEFAULT_SPEED / MAX_SPEED) * (GameInfo.speed - 1));
}

void incGameLevel(void) {
  if (GameInfo.level < MAX_LEVEL) GameInfo.level++;
}

void incGameSpeed(void) {
  if (GameInfo.speed < MAX_SPEED) GameInfo.speed++;
}

void decGameLevel(void) {
  if (GameInfo.level > 1) GameInfo.level--;
}

void decGameSpeed(void) {
  if (GameInfo.speed > 1) GameInfo.speed--;
}

int getGameState(void) { return GameInfo.state; }
int getGameLevel(void) { return GameInfo.level; }
int getGameSpeed(void) { return GameInfo.speed; }
int getGameScore(void) { return GameInfo.score; }
int getGameHighScore(void) { return GameInfo.high_score; }

int getCurrFigCell(int y, int x) {
  return Figures[getCurrFigType()][getCurrFigRotation()][y][x];
}

void setGameInfoNext(void) {
  GameInfo.next = Figures[getNextFigType()][getNextFigRotation()];
}

void setFieldCell(int y, int x, int val) { GameInfo.field[y][x] = val; }
int getFieldCell(int y, int x) { return GameInfo.field[y][x]; }
