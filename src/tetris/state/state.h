#ifndef STATE_H 
#define STATE_H

/**
 * @brief Состояния игры
 *
 * Определяет различные состояния, в которых может находиться игра.
 */
typedef enum {
  State0,  ///< Начальное состояние (неинициализировано)
  StateInit,    ///< Инициализация игры
  StateIdle,    ///< Ожидание действий пользователя
  StateSpawn,   ///< Спавн новой фигуры
  StateAction,  ///< Действия игрока
  StateShift,   ///< Сдвиг фигуры
} GameState_t;

/**
 * @brief Устанавливает новое игровое состояние
 * 
 * @param newState Новое состояние игры (значение из перечисления GameState_t).
 */
void setGameState(int);

/**
 * @brief Возвращает текущее состояние игры
 * 
 * @return Текущее состояние игры (значение из перечисления GameState_t).
 */
int getGameState(void);


#endif //STATE_H
