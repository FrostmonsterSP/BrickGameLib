PROJECT_NAME:=brick_game_lib
PROJECT_VER:=2.3

# Компилятор и флаги
CC=gcc
AR=ar rcs
GCOVR=gcovr
DOXYGEN=doxygen/doxygen
PIPE=>/dev/null 2>&1
G=@

RM=rm -rf
CFLAGS+=-Wall -Werror -Wextra -pedantic -std=c11 -Isrc -O2 -fPIC
CLIBS=-lbrick -lncurses
TEST_LIBS=-lcheck -ltetristest -lncurses -lgcov -lm -lsubunit
COV_FLAGS=-fprofile-arcs -ftest-coverage

# Папки
OBJ_DIR=obj
TOBJ_DIR=$(OBJ_DIR)/test
TETRIS_DIR=src/tetris
LIB_DIR=lib
TEST_DIR=tests
REPORT_DIR=report
BIN_DIR=bin
HTML_DOC_DIR=doc/html

# Исходные файлы
TETRIS_SRCS=$(wildcard $(TETRIS_DIR)/*.c)
GUI_SRCS=$(wildcard $(GUI_DIR)/*.c)
TEST_SRCS=$(wildcard $(TEST_DIR)/*.c)

# Объектные файлы
TETRIS_OBJS=$(patsubst $(TETRIS_DIR)/%.c, $(OBJ_DIR)/%.o, $(TETRIS_SRCS))
GUI_OBJS=$(patsubst $(GUI_DIR)/%.c, $(OBJ_DIR)/%.o, $(GUI_SRCS))
MAIN_OBJ=$(patsubst %.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

# Объектные файлы тестов
TEST_OBJS=$(patsubst $(TEST_DIR)/%.c, $(TOBJ_DIR)/%.o, $(TEST_SRCS))
TTETRIS_OBJS=$(patsubst $(TETRIS_DIR)/%.c, $(TOBJ_DIR)/%.o, $(TETRIS_SRCS))
TGUI_OBJS=$(patsubst $(GUI_DIR)/%.c, $(TOBJ_DIR)/%.o, $(GUI_SRCS))

# Исполняемый файл и библиотеки
LIB_TETRIS_A=$(LIB_DIR)/libtetris.a
TLIB_TETRIS_A=$(LIB_DIR)/libtetristest.a
LIB_TETRIS_SO=$(LIB_DIR)/libtetris.so
TLIB_TETRIS_SO=$(LIB_DIR)/libtetristest.so
LIB_DIR_LINK=-L$(LIB_DIR)
DISTFILE=$(PROJECT_NAME)-$(PROJECT_VER).${shell uname -m}.tar.gz

# Документация
HTML_DOC=$(HTML_DOC_DIR)/index.html
GCOV_REPORT=$(REPORT_DIR)/coverage.html

# Цвета для вывода в консоль
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
BOLD=\033[1m
RESET=\033[0m

ifeq ($(shell uname),Darwin)
OPEN_CMD=open
endif

ifeq ($(shell uname),Linux)
OPEN_CMD=xdg-open
ADD_LDFLAGS=-lm -lsubunit
endif

ifeq ($(DEBUG), 1)
G=
PIPE=
endif

ifneq ($(DOXYPATH),)
DOXYGEN=$(DOXYPATH)
endif

.PHONY: test build rebuild gcov_report dvi clean clean-test clean-test-obj clean-test-lib clean-obj clean-lib clean-doc clean-report clean-dist purge everything rebuild-all

# Правило по умолчанию
all: test build

# Создание директорий для объектных файлов, библиотек и исполняемого файла
$(OBJ_DIR):
	@if test ! -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога сборки${RESET}\n"; mkdir -p $(OBJ_DIR); fi

$(LIB_DIR):
	@if test ! -d $(LIB_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога библиотек${RESET}\n"; mkdir -p $(LIB_DIR); fi

$(REPORT_DIR):
	@if test ! -d $(REPORT_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога отчёта${RESET}\n"; mkdir -p $(REPORT_DIR); fi

$(TOBJ_DIR):
	@if test ! -d $(TOBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога сборки тестов${RESET}\n"; mkdir -p $(TOBJ_DIR); fi

$(BIN_DIR):
	@if test ! -d $(BIN_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Создание каталога исполняемого файла${RESET}\n"; mkdir -p $(BIN_DIR); fi

# Сборка тестов
test: $(TOBJ_DIR) $(LIB_DIR) $(TGUI_OBJS) $(TLIB_TETRIS_A) $(TEST_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка тестов${RESET}\n"
	$(G)$(CC) $(CFLAGS) $(COV_FLAGS) -o $@ $(TEST_OBJS) $(TGUI_OBJS) $(LIB_DIR_LINK) $(TEST_LIBS)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Запуск тестов${RESET}\n"
	$(G)./$@

# Создание статической библиотеки движка
$(LIB_TETRIS_A): $(LIB_DIR) $(OBJ_DIR) $(TETRIS_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка статической библиотеки движка $(notdir $@)${RESET}\n"
	$(G)$(AR) $@ $(TETRIS_OBJS)

# Создание динамической библиотеки движка
$(LIB_TETRIS_SO): $(LIB_DIR) $(OBJ_DIR) $(TETRIS_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка динамической библиотеки движка $(notdir $@)${RESET}\n"
	$(G)$(CC) $(CFLAGS) -shared -o $@ $(TETRIS_OBJS)

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(TETRIS_DIR)/%.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GUI_DIR)/%.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) -c $< -o $@

# Создание статической библиотеки движка для тестов
$(TLIB_TETRIS_A): $(TTETRIS_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка тестовой статической библиотеки движка $(notdir $@)${RESET}\n"
	$(G)$(AR) $@ $^

# Создание статической библиотеки GUI для тестов
$(TLIB_GUI_OBJ): $(TGUI_OBJS)
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Сборка тестовой статической библиотеки интерфейса $(notdir $@)${RESET}\n"
	$(G)$(AR) $@ $^

# Компиляция объектных файлов для тестов
$(TOBJ_DIR)/%.o: $(TETRIS_DIR)/%.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция тестового $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

$(TOBJ_DIR)/%.o: $(GUI_DIR)/%.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция тестового $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

# Компиляция тестов
$(TOBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@printf "${BLUE}${BOLD}=>${RESET}${BLUE} Компиляция тестов $(notdir $<)${RESET}\n"
	$(G)$(CC) $(CFLAGS) -c $< -o $@

# Очистка отчёта о покрытии тестов
clean-report:
	@if test -d $(REPORT_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление отчёта о покрытии тестов${RESET}\n"; $(RM) $(REPORT_DIR); fi

# Очистка документации
clean-doc:
	@if test -d $(HTML_DOC_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление html документации${RESET}\n"; $(RM) $(HTML_DOC_DIR); fi

# Очистка тестов
clean-test: clean-test-obj clean-test-lib
	@if test -f test; then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление тестового файла${RESET}\n"; $(RM) test; fi

clean-test-obj:
	@if test -d $(TOBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога сборки тестов${RESET}\n"; $(RM) $(TOBJ_DIR); fi

clean-test-lib:
	@if test -f $(TLIB_TETRIS_A); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление тестовой статической библиотеки движка${RESET}\n"; $(RM) $(TLIB_TETRIS_A); fi

# Очистка библиотек
clean-lib:
	@if test -d $(LIB_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога библиотек${RESET}\n"; $(RM) $(LIB_DIR); fi

# Очистка объектных файлов
clean-obj:
	@if test -d $(OBJ_DIR); then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление каталога сборки${RESET}\n"; $(RM) $(OBJ_DIR); fi

# Очистка старого архива:
clean-dist:
	@if test -f "$(DISTFILE)"; then printf "${PURPLE}${BOLD}=>${RESET}${PURPLE} Удаление старого архива $(DISTFILE)${RESET}\n"; $(RM) $(DISTFILE); fi

clean: clean-test clean-test-obj clean-test-lib clean-obj

# Пересборка
rebuild: clean all

$(GCOV_REPORT): $(REPORT_DIR)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Генерация отчёта о покрытии тестов${RESET}\n"
	$(G)$(GCOVR) --html-details $(GCOV_REPORT) --html-theme github.dark-blue $(PIPE)

# Генерация отчёта о покрытии тестов
gcov_report: test $(GCOV_REPORT)
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Открытие отчёта о покрытии тестов${RESET}\n"
	$(G)$(OPEN_CMD) $(GCOV_REPORT)

build: $(LIB_TETRIS_A) $(LIB_TETRIS_SO)

# Цель install
install: $(BIN_DIR) build
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Установка исполняемого файла${RESET}\n"
	$(G)mv $(EXEC) $(BIN_DIR)
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Установка завершена${RESET}\n"

# Генерация документации
$(HTML_DOC):
	@if test ! -d $(HTML_DOC_DIR); then printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Генерация документации${RESET}\n" ; fi
	@if test ! -d $(HTML_DOC_DIR); then $(DOXYGEN) $(PIPE); fi;

dvi: $(HTML_DOC)
	@printf "${GREEN}${BOLD}=>${RESET}${GREEN} Открытие html документации${RESET}\n"
	$(G)$(OPEN_CMD) $(HTML_DOC)

# Создание tar архива
dist: clean-dist build
	@printf "${YELLOW}${BOLD}=>${RESET}${YELLOW} Создание архива $(DISTFILE)${RESET}\n"
	$(G)cp src/engine.h engine.h
	$(G)tar -czf $(DISTFILE) $(LIB_DIR) engine.h
	$(G)rm engine.h

# Полная чистка
purge: clean clean-lib clean-report clean-doc clean-dist 

# Полная сборка (все цели)
everything: all $(GCOV_REPORT) $(HTML_DOC) dist

# Полная пересборка
rebuild-all: purge everything
