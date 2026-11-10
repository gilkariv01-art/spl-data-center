CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -Iinclude

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/spl_data_center

all: $(BIN_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)/* $(TARGET)
