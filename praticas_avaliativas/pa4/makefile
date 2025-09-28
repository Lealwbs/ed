CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

INCLUDE_FOLDER = ./include
BIN_FOLDER = ./bin
OBJ_FOLDER = ./obj
SRC_FOLDER = ./src

TARGET = pa4
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)/%.cpp, $(OBJ_FOLDER)/%.o, $(SRC))
# INPUT_ARGV = ''

ifeq ($(OS),Windows_NT)
	EXEC_EXT = .exe
	CLEAR = cls
else
	EXEC_EXT = .out
	CLEAR = clear
endif

all: dirs $(BIN_FOLDER)/$(TARGET)$(EXEC_EXT)

$(BIN_FOLDER)/$(TARGET)$(EXEC_EXT): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

dirs:
	@mkdir -p $(OBJ_FOLDER)
	@mkdir -p $(BIN_FOLDER)

run: all
	$(CLEAR)
	$(BIN_FOLDER)/$(TARGET)$(EXEC_EXT) $(INPUT_ARGV)

clean:
	@rm -rf $(OBJ_FOLDER)/* $(BIN_FOLDER)/*