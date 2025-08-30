#ifndef CURRENT_FIGURE_H
#define CURRENT_FIGURE_H

/**
 * @brief Возвращает поворот следующей фигуры
 * @return поворот следующей фигуры (int 0-3)
 */
int getNextFigRotation(void);

/**
 * @brief Возвращает тип следующей фигуры
 * @return тип следующей фигуры (int 0-6)
 */
int getNextFigType(void);

/**
 * @brief Инициализирует следующую фигуру
 *
 * @details Функция генерирует случайный тип и поворот для следующей фигуры, а
 * затем вызывает setGameInfoNext() для установки указателя GameInfo.next на
 * двухмерный массив фигуры **Figures[][]
 */
void newNextFigure(void);

#endif // CURRENT_FIGURE_H
