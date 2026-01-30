CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -Iutils

SRC_DIR := src
UTILS_DIR := utils
OBJ_DIR := build
TARGET := sga.exe

SRC_FILES := main lista pila cola calificaciones
UTIL_FILES := archivos validaciones

SRC_OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
UTIL_OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(UTIL_FILES)))
OBJS := $(SRC_OBJS) $(UTIL_OBJS)

vpath %.cpp $(SRC_DIR) $(UTILS_DIR)

.PHONY: all clean run dirs

all: dirs $(TARGET)

dirs: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp | dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

