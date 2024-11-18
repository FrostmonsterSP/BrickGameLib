/**
 * @file next_figure.c
 * @brief Реализации функций для работы со следующей фигурой
 *
 * @details Функции, реализованные в этом файле, предназначены для работы со
 * следующей фигурой: получения типа и поворота, задания типа и поворота,
 * инициализации следующей фигуры.
 */
#include <engine.h>
#include <stdlib.h>
#include <time.h>

#include "private.h"

static int NextFigureType = -1;  ///< Тип следующей фигуры
static int NextFigureRotation = -1;  ///< Поворот следующей фигуры

void newNextFigure(void) {
  srand(time(NULL));
  NextFigureType = (FigType_t)(rand() % FIGURE_CNT);
  NextFigureRotation = (Rotation_t)(rand() % FIGURE_ROUNDS);
  setGameInfoNext();
}

int getNextFigType(void) { return NextFigureType; }
int getNextFigRotation(void) { return NextFigureRotation; }
