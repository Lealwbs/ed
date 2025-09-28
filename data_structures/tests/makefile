# Makefile simples para Windows
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Diretórios
SRC_DIR = ..
BIN_DIR = bin
OBJ_DIR = obj
CPP_UNIT_DIR = ../../cpp_unit_test

# Targets principais
compile: $(BIN_DIR)/list_test.exe $(BIN_DIR)/queue_test.exe

# Compilar teste da lista
$(BIN_DIR)/list_test.exe: list_test.cpp $(OBJ_DIR)/list.o $(OBJ_DIR)/assert.o
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include list_test.cpp $(OBJ_DIR)/list.o $(OBJ_DIR)/assert.o -o $(BIN_DIR)/list_test.exe

# Compilar teste da fila
$(BIN_DIR)/queue_test.exe: queue_test.cpp $(OBJ_DIR)/queue.o $(OBJ_DIR)/assert.o
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include queue_test.cpp $(OBJ_DIR)/queue.o $(OBJ_DIR)/assert.o -o $(BIN_DIR)/queue_test.exe

# Compilar objeto da lista
$(OBJ_DIR)/list.o: $(SRC_DIR)/list/list.cpp
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include -c $(SRC_DIR)/list/list.cpp -o $(OBJ_DIR)/list.o

# Compilar objeto da fila
$(OBJ_DIR)/queue.o: $(SRC_DIR)/queue/queue.cpp
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(CPP_UNIT_DIR)/include -c $(SRC_DIR)/queue/queue.cpp -o $(OBJ_DIR)/queue.o

# Compilar objeto do assert
$(OBJ_DIR)/assert.o: $(CPP_UNIT_DIR)/src/assert.cpp
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(CXX) $(CXXFLAGS) -I$(CPP_UNIT_DIR)/include -c $(CPP_UNIT_DIR)/src/assert.cpp -o $(OBJ_DIR)/assert.o

# Executar teste da lista
test_list: $(BIN_DIR)/list_test.exe
	cls
	@echo Executando teste da lista...
	@$(BIN_DIR)/list_test.exe

# Executar teste da fila
test_queue: $(BIN_DIR)/queue_test.exe
	@echo Executando teste da fila...
	@$(BIN_DIR)/queue_test.exe

# Limpar arquivos compilados
clean:
	@echo Limpando arquivos...
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	@echo Limpeza concluida!

# Ajuda
help:
	@echo Comandos disponiveis:
	@echo.
	@echo   make test_list   - Executa teste da lista
	@echo   make test_queue  - Executa teste da fila
	@echo   make compile     - Compila todos os testes
	@echo   make clean       - Remove arquivos compilados
	@echo   make help        - Mostra esta ajuda
	@echo.

.PHONY: compile test_list test_queue clean help