# Makefile for C++ project in the Skeleton folder

# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Weffc++

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Source files
SRC_FILES = $(SRC_DIR)/main.cpp \
            $(SRC_DIR)/Customer.cpp \
            $(SRC_DIR)/WareHouse.cpp \
			$(SRC_DIR)/Action.cpp \
            $(SRC_DIR)/Order.cpp \
			$(SRC_DIR)/Volunteer.cpp
HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES))

# Libraries
LIBS = -lstdc++

# Executable name
EXECUTABLE = TEST

# Targets
all: clean compile link

link: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(EXECUTABLE) $(OBJ_FILES) $(LIBS)

compile: $(OBJ_FILES)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INCLUDE_DIR)

clean:
	rm -f $(BIN_DIR)/*

.PHONY: all clean
