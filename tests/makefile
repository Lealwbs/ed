# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
INCLUDE_FOLDER = ./include
BIN_FOLDER = ./bin
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src

# all sources, objs, and header files
TARGET = run_tests
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)/%.cpp, $(OBJ_FOLDER)/%.o, $(SRC))
# TEXT_FILES = ./files/tests/teste10.txt

# OS detection
ifeq ($(OS),Windows_NT)
	EXEC_EXT = .exe
	CLEAR = cls
else
	EXEC_EXT = .out
	CLEAR = clear
endif

# Default target
all: create_dirs $(BIN_FOLDER)/$(TARGET)$(EXEC_EXT)

# Linking
$(BIN_FOLDER)/$(TARGET)$(EXEC_EXT): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

# Compilation
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Create necessary folders
create_dirs:
	@mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)

# Run
run: all
	$(CLEAR)
	$(BIN_FOLDER)/$(TARGET)$(EXEC_EXT)

# Clean
clean:
	@rm -rf $(OBJ_FOLDER)/* $(BIN_FOLDER)/*

.PHONY: all run clean create_dirs