CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# Estrutura de diretórios
INCLUDE_FOLDER = ./include
SRC_FOLDER = ./src
BIN_FOLDER = bin
OBJ_FOLDER = obj

TARGET = list_run
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)/%.cpp, $(OBJ_FOLDER)/%.o, $(SRC))
# INPUT_ARGV = ''

# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
	EXEC_EXT = .exe
	CLEAR = cls
	CREATE_DIR = if not exist
	DEL_COMMAND = del /Q
	/ = \\
	DELETE_DIR1 = if exist $(OBJ_FOLDER) rmdir $(OBJ_FOLDER)
	DELETE_DIR2 = if exist $(BIN_FOLDER) rmdir $(BIN_FOLDER)
else
	EXEC_EXT = .out
	CLEAR = clear
	CREATE_DIR = @mkdir -p
	DEL_COMMAND = rm -f
	/ = /
endif

all: dirs $(BIN_FOLDER)/$(TARGET)$(EXEC_EXT)

$(BIN_FOLDER)/$(TARGET)$(EXEC_EXT): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Criação dos diretórios se não existirem
dirs:
	$(CREATE_DIR) $(BIN_FOLDER) mkdir $(BIN_FOLDER)
	$(CREATE_DIR) $(OBJ_FOLDER) mkdir $(OBJ_FOLDER)

# Compilar e executar o programa com um único comando
run: all
	$(CLEAR)
	$(BIN_FOLDER)$(/)$(TARGET)$(EXEC_EXT) $(INPUT_ARGV)

# Limpar os arquivos compilados e apagar os diretórios
clean:
	-$(DEL_COMMAND) $(OBJ_FOLDER)$(/)* $(BIN_FOLDER)$(/)*
	$(DELETE_DIR1) 
	$(DELETE_DIR2)

clear: clean