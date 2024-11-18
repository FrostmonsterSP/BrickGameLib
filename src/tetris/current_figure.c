/**
 * @file current_figure.c
 * @brief Реализации функций для работы с текущей фигурой
 *
 * @details Функции, реализованные в этом файле, предназначены для работы с
 * текущей фигурой: получения координат, типа и поворота, задания типа и
 * поворота, инициализации текущей фигуры, движения, вращения, проверки
 * возможности движения, записи фигуры на поле, очистки фигуры, инициализации
 * следующей фигуры.
 */
#include "current_figure.h"

#include <engine.h>

#include "private.h"

/** Структура типа Figure_t для текущей фигуры  */
static Figure_t CurrFigure = {0};

void setLeftEdge(void) {
  int rows = FIGURE_HEIGHT;
  CurrFigure.left_edge = 0;
  for (int i = 0; i < FIGURE_WIDTH && rows == FIGURE_HEIGHT; i++) {
    rows = 0;
    for (int j = 0; j < FIGURE_HEIGHT && !getCurrFigCell(j, i); j++) {
      rows++;
    }
    CurrFigure.left_edge += rows / FIGURE_HEIGHT;
  }
}

void setRightEdge(void) {
  int rows = FIGURE_HEIGHT;
  CurrFigure.right_edge = 0;
  for (int i = FIGURE_WIDTH - 1; i >= 0 && rows == FIGURE_HEIGHT; i--) {
    rows = 0;
    for (int j = 0; j < FIGURE_HEIGHT && !getCurrFigCell(j, i); j++) {
      rows++;
    }
    CurrFigure.right_edge += rows / FIGURE_HEIGHT;
  }
}

void rowsToCheck(void) {
  for (int i = 0; i < FIGURE_WIDTH; i++) {
    CurrFigure.rows_next_line[i] = -1;
    for (int j = FIGURE_HEIGHT - 1; j >= 0 && CurrFigure.rows_next_line[i] <= 0;
         j--) {
      if (getCurrFigCell(j, i)) {
        CurrFigure.rows_next_line[i] = j;
      }
    }
  }
}

void rotateCurrFig(void) {
  Rotation_t new_rotation = (CurrFigure.rotation + 1) % FIGURE_ROUNDS;
  int overlap = 0;
  for (int i = 0; !overlap && i < FIGURE_HEIGHT; i++) {
    for (int j = 0; !overlap && j < FIGURE_WIDTH; j++) {
      int figure_cell = getCurrFigCell(0, i);
      int field_cell = getFieldCell(CurrFigure.y + i, CurrFigure.x + j);
      overlap = figure_cell && field_cell;
    }
  }
  if (!overlap) {
    CurrFigure.rotation = new_rotation;
    setLeftEdge();
    setRightEdge();
    rowsToCheck();
    if (CurrFigure.x - CurrFigure.right_edge + FIGURE_WIDTH > FIELD_WIDTH) {
      CurrFigure.x = FIELD_WIDTH - FIGURE_WIDTH + CurrFigure.right_edge;
    } else if (CurrFigure.x - CurrFigure.left_edge < 0) {
      CurrFigure.x = 0 - CurrFigure.left_edge;
    }
  }
}

void setNewCurrFig(void) {
  CurrFigure.type = getNextFigType();
  CurrFigure.rotation = getNextFigRotation();
  newNextFigure();
  CurrFigure.x = FIELD_WIDTH / 2 - 2;
  CurrFigure.y = -1;
  setLeftEdge();
  setRightEdge();
  rowsToCheck();
}

void moveCurrFig(int direction) {
  int edge = CurrFigure.left_edge - 1;
  int j = CurrFigure.left_edge;
  int edge_of_field = (CurrFigure.x + edge) < 0;
  if (direction) {
    edge = FIGURE_WIDTH - CurrFigure.right_edge;
    j = CurrFigure.right_edge;
    edge_of_field = (CurrFigure.x + edge) > (FIELD_WIDTH - 1);
  }
  int block_collision = 0;
  for (int i = 0; !edge_of_field && !block_collision && i < FIGURE_HEIGHT;
       i++) {
    if (getCurrFigCell(i, j)) {
      block_collision = getFieldCell(CurrFigure.y + i, CurrFigure.x + edge);
    }
  }
  if (!edge_of_field && !block_collision) {
    CurrFigure.x += direction ? 1 : -1;
  }
}

int checkNextLine(void) {
  int result = 1;
  for (int i = 0; i < FIGURE_WIDTH && result; i++) {
    if (CurrFigure.rows_next_line[i] >= 0) {
      int field_y = CurrFigure.y + CurrFigure.rows_next_line[i] + 1;
      int field_x = CurrFigure.x + i;
      result = field_y < FIELD_HEIGHT && !(getFieldCell(field_y, field_x));
    }
  }
  return result;
}

void putCurrFig(void) {
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int field_y = CurrFigure.y + i;
      int field_x = CurrFigure.x + j;
      unsigned cell_on_field_y = field_y < FIELD_HEIGHT && field_y >= 0;
      unsigned cell_on_field_x = field_x < FIELD_WIDTH && field_x >= 0;
      if (getCurrFigCell(i, j) == 1 && cell_on_field_y && cell_on_field_x) {
        setFieldCell(field_y, field_x, 1);
      }
    }
  }
}

void clearCurrFig(void) {
  int curr_y = getCurrFigCoordY();
  int curr_x = getCurrFigCoordX();
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      if (getCurrFigCell(i, j)) {
        setFieldCell(curr_y + i, curr_x + j, 0);
      }
    }
  }
}

void moveCurrFigDown(void) { CurrFigure.y++; }

int getCurrFigCoordX(void) { return CurrFigure.x; }
int getCurrFigCoordY(void) { return CurrFigure.y; }
int getCurrFigType(void) { return CurrFigure.type; }
int getCurrFigRotation(void) { return CurrFigure.rotation; }
int getCurrFigLeftEdge(void) { return CurrFigure.left_edge; }
int getCurrFigRightEdge(void) { return CurrFigure.right_edge; }
int getCurrFigRowsToCheck(int i) { return CurrFigure.rows_next_line[i]; }

void setCurrFigType(int type) { CurrFigure.type = type; }
void setCurrFigCoordX(int x) { CurrFigure.x = x; }
void setCurrFigCoordY(int y) { CurrFigure.y = y; }
void setCurrFigRotation(int rotation) { CurrFigure.rotation = rotation; }
